#pragma once

#include <string>

class HttpResponse {
    public:
        HttpResponse(int statuscode, std::string const& data);
        ~HttpResponse();
        int statuscode;
        std::string data;
};