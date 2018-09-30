#pragma once

#include "HttpResponse.h"
#include <curl/curl.h>
#include <string>

class HttpClient {
    public:
        HttpClient();
        HttpResponse * get(const char *url);
        HttpResponse * post(const char *url, const char* data);
        HttpResponse * put(const char *url, const char* data);
    private:
        CURL *handle;
        static size_t invoke_write_data (void *ptr, size_t size, size_t nmemb, std::string* data);
};
