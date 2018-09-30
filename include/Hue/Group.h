#pragma once

#include <cJson.h>

class Group {
    public:
        char * id;
        char * name;
        static Group * fromJson(cJSON * json);
};