#include "Hue/Group.h"
#include <cJson.h>
#include <stdio.h>


Group::Group()
{
    lights = new vector<Light*>;
    lightIds = new vector<char*>;
    anyOn = false;
    allOn = false;
}

Group * Group::fromJson(cJSON * json) {
    Group * group = new Group();

    group->id = json->string;
    group->name = cJSON_GetObjectItem(json, "name")->valuestring;
    if(cJSON_HasObjectItem(json, "state")) {
        cJSON *state = cJSON_GetObjectItem(json, "state");
        group->allOn = cJSON_IsTrue(cJSON_GetObjectItem(state, "all_on"));
        group->anyOn = cJSON_IsTrue(cJSON_GetObjectItem(state, "any_on"));
    }
    if(cJSON_HasObjectItem(json, "lights")) {
        cJSON *lights = cJSON_GetObjectItem(json, "lights");
        for(int i = 0; i < cJSON_GetArraySize(lights); i++) {
            group->lightIds->push_back(cJSON_GetArrayItem(lights, i)->valuestring);
        }
        
    }

    return group;
}

void Group::print()
{
    printf("Name: %s\n", name);
    printf("AnyOn: %s\n", anyOn ? "true" : "false");
    printf("AllOn: %s\n", allOn ? "true" : "false");

    printf("Lights: %d\n", lights->size());
    for(int i = 0; i < lights->size(); i++) {
        lights->at(i)->print();
    }
}