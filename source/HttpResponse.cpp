#include "HttpResponse.h"
#include <stdlib.h>
#include <string.h>

HttpResponse::HttpResponse(int statuscode, std::string const& data) {
    this->statuscode = statuscode;
    this->data = data;
}

HttpResponse::~HttpResponse() {
    //free(this->data);
}