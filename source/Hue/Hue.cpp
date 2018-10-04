#include "Hue/Hue.h"
#include "Hue/Light.h"
#include "HttpClient.h"
#include "HttpResponse.h"
#include "cJson.h"
#include <stdio.h>
#include <math.h>
#include <cstring>

Hue::Hue() {
    mHttpClient = new HttpClient();
    mMdnsHelper = new MdnsHelper();
    ip = NULL;
    user = NULL;
}

void Hue::setUser(char * user) {
    this->user = user;
}

void Hue::setIp(char * ip) {
    this->ip = ip;
}

char* Hue::getIp() {
    return this->ip;
}

char * Hue::discoverByNupnp() {
    HttpResponse * response = mHttpClient->get("https://www.meethue.com/api/nupnp");

    cJSON *json = cJSON_Parse(response->data.c_str());
    if(cJSON_GetArraySize(json) == 0) {
        return NULL;
    }

    cJSON *bridge = cJSON_GetArrayItem(json, 0);
    cJSON *internalipaddress = cJSON_GetObjectItem(bridge, "internalipaddress");
    this->ip = cJSON_GetStringValue(internalipaddress);    

    delete response;
    cJSON_free(json);

    return this->ip;
}

void Hue::discoverByMdns() {
    this->setIp(mMdnsHelper->discover());
}

char * Hue::registerUser() {
    char url[50];
    sprintf(url, "http://%s/api", this->ip);
    
    HttpResponse * response = mHttpClient->post(url, "{\"devicetype\":\"hue3ds#3ds\"}");

    cJSON *json = cJSON_Parse(response->data.c_str());
    cJSON *obj = cJSON_GetArrayItem(json, 0);
    if(cJSON_HasObjectItem(obj, "error")) {
        delete response;
        cJSON_free(json);
        return NULL;
    }

    cJSON *success = cJSON_GetObjectItem(obj, "success");
    cJSON *username = cJSON_GetObjectItem(success, "username");
    char * user = cJSON_GetStringValue(username);
    
    delete response;
    cJSON_free(json);

    return user;
}

vector<Light> * Hue::getLights() {
    vector<Light> * lights = new vector<Light>;
    
    char url[100];
    sprintf(url, "http://%s/api/%s/lights", this->ip, this->user);
    HttpResponse * response = mHttpClient->get(url);

    cJSON * json = cJSON_Parse(response->data.c_str());
    cJSON * light = NULL;
    cJSON_ArrayForEach(light, json) {
        lights->push_back(*Light::fromJson(light));
    }

    cJSON_free(json);
    delete response;

    return lights;
}

bool Hue::setOnState(char * id, bool state) {
    HttpResponse * response = NULL;
    char url[100];
    sprintf(url, "http://%s/api/%s/lights/%s/state", this->ip, this->user, id);

    if(state) {
        response = mHttpClient->put(url, "{\"on\":true}");
    }
    else {
        response = mHttpClient->put(url, "{\"on\":false}");
    }

    bool success = response->statuscode == 200;
    delete response;

    return success;
}

bool Hue::setColorXy(char * id, double x, double y) {
    HttpResponse * response = NULL;
    char url[100];
    sprintf(url, "http://%s/api/%s/lights/%s/state", this->ip, this->user, id);

    char json[100];
    sprintf(json, "{\"xy\":[%.6f, %.6f]}", x, y);
    response = mHttpClient->put(url, json);

    bool success = response->statuscode == 200;
    delete response;

    return success;
}

bool Hue::setColorRgb(char *id, double red, double green, double blue) {
    float r = (red   > 0.04045f) ? pow((red   + 0.055f) / (1.0f + 0.055f), 2.4f) : (red   / 12.92f);
    float g = (green > 0.04045f) ? pow((green + 0.055f) / (1.0f + 0.055f), 2.4f) : (green / 12.92f);
    float b = (blue  > 0.04045f) ? pow((blue  + 0.055f) / (1.0f + 0.055f), 2.4f) : (blue  / 12.92f);

    float X = r * 0.664511f + g * 0.154324f + b * 0.162028f;
    float Y = r * 0.283881f + g * 0.668433f + b * 0.047685f;
    float Z = r * 0.000088f + g * 0.072310f + b * 0.986039f;

    float cx = X / (X + Y + Z);
    float cy = Y / (X + Y + Z);

    if (isnan(cx)) {
        cx = 0.0f;
    }

    if (isnan(cy)) {
        cy = 0.0f;
    }

    return this->setColorXy(id, cx, cy);
}

vector<Group> * Hue::getGroups() {
    vector<Group> * groups = new vector<Group>;

    char url[100];
    sprintf(url, "http://%s/api/%s/groups", this->ip, this->user);
    HttpResponse * response = mHttpClient->get(url);

    cJSON * json = cJSON_Parse(response->data.c_str());
    cJSON * group = NULL;
    cJSON_ArrayForEach(group, json) {
        groups->push_back(*Group::fromJson(group));
    }

    cJSON_free(json);
    delete response;

    return groups;
}

Group* Hue::getGroupById(char * id)
{
    char url[100];
    sprintf(url, "http://%s/api/%s/groups/%s", this->ip, this->user, id);
    HttpResponse * response = mHttpClient->get(url);

    cJSON * json = cJSON_Parse(response->data.c_str());
    Group* group = Group::fromJson(json);
    vector<Light>* lights = getLights();

    for(int i = 0; i < group->lightIds->size(); i++) {
        char* id = group->lightIds->at(i);

        for(int j = 0; j < lights->size(); j ++) {
            if(strcmp(lights->at(j).id, id) == 0) {
                group->lights->push_back(&lights->at(j));
            }
        }
    }

    return group;
}

bool Hue::setGroupOnState(char * id, bool state) {
    HttpResponse * response = NULL;
    char url[100];
    sprintf(url, "http://%s/api/%s/groups/%s/action", this->ip, this->user, id);

    if(state) {
        response = mHttpClient->put(url, "{\"on\":true}");
    }
    else {
        response = mHttpClient->put(url, "{\"on\":false}");
    }

    bool success = response->statuscode == 200;
    delete response;

    return success;
}

bool Hue::setGroupColorXy(char * id, double x, double y) {
    HttpResponse * response = NULL;
    char url[100];
    sprintf(url, "http://%s/api/%s/groups/%s/action", this->ip, this->user, id);

    char json[100];
    sprintf(json, "{\"xy\":[%.6f, %.6f]}", x, y);
    response = mHttpClient->put(url, json);

    bool success = response->statuscode == 200;
    delete response;

    return success;
}

bool Hue::setGroupColorRgb(char *id, double red, double green, double blue) {
    float r = (red   > 0.04045f) ? pow((red   + 0.055f) / (1.0f + 0.055f), 2.4f) : (red   / 12.92f);
    float g = (green > 0.04045f) ? pow((green + 0.055f) / (1.0f + 0.055f), 2.4f) : (green / 12.92f);
    float b = (blue  > 0.04045f) ? pow((blue  + 0.055f) / (1.0f + 0.055f), 2.4f) : (blue  / 12.92f);

    float X = r * 0.664511f + g * 0.154324f + b * 0.162028f;
    float Y = r * 0.283881f + g * 0.668433f + b * 0.047685f;
    float Z = r * 0.000088f + g * 0.072310f + b * 0.986039f;

    float cx = X / (X + Y + Z);
    float cy = Y / (X + Y + Z);

    if (isnan(cx)) {
        cx = 0.0f;
    }

    if (isnan(cy)) {
        cy = 0.0f;
    }

    return this->setGroupColorXy(id, cx, cy);
}

bool Hue::setBrightness(char * id, int brightness) {
    HttpResponse * response = NULL;
    char url[100];
    sprintf(url, "http://%s/api/%s/lights/%s/state", this->ip, this->user, id);

    char json[100];
    sprintf(json, "{\"bri\":%d}", brightness);
    response = mHttpClient->put(url, json);

    bool success = response->statuscode == 200;
    delete response;

    return success;
}

bool Hue::setGroupBrightness(char * id, int brightness) {
    HttpResponse * response = NULL;
    char url[100];
    sprintf(url, "http://%s/api/%s/groups/%s/action", this->ip, this->user, id);

    char json[100];
    sprintf(json, "{\"bri\":%d}", brightness);
    response = mHttpClient->put(url, json);

    bool success = response->statuscode == 200;
    delete response;

    return success;
}

