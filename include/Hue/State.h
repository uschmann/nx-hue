#pragma once

#include <cJSON.h>

class State {
    public:
        bool on;
        int bri;
        int hue;
        int sat;
        int ct;
        double colorX;
        double colorY;
        bool reachable;
        char * colormode;
        static State * fromJson(cJSON * json);
};