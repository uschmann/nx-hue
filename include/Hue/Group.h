#pragma once

#include <cJson.h>
#include "vector"
#include "Hue/Light.h"

using namespace std;

class Group {
    public:
        Group();
        char * id;
        char * name;
        vector<Light*>* lights;
        vector<char *>* lightIds;
        bool anyOn;
        bool allOn;

        static Group * fromJson(cJSON * json);

        void print();
};