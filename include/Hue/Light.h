#pragma once

#include "State.h"
#include <cJson.h>

class Light {
    public: 
        char * id;
        char * name;
        char * type;
        char * modelid;
        char * swversion;
        char * productid;
        char * archetype;
        State * state;

        static Light * fromJson(cJSON * json);

        void print();
};
