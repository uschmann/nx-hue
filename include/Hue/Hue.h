#pragma once

#include <vector>
#include "HttpClient.h"
#include "Light.h"
#include "Group.h"

using namespace std;

class Hue {
    public:
        Hue();
        char * discoverByNupnp();
        void setUser(char * user);
        void setIp(char * ip);
        char* getIp();
        char * registerUser();

        vector<Light> * getLights();
        bool setOnState(char * id, bool state);
        bool setColorRgb(char *id, double red, double green, double blue);
        bool setColorXy(char *id, double x, double y);
        bool setBrightness(char * id, int brightness);

        vector<Group> * getGroups();
        bool setGroupOnState(char * id, bool state);
        bool setGroupColorRgb(char *id, double red, double green, double blue);
        bool setGroupColorXy(char *id, double x, double y);
        bool setGroupBrightness(char * id, int brightness);
    protected:
        HttpClient *mHttpClient;
        char * ip;
        char * user;
};