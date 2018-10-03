#include <HttpClient.h>
#include <HttpResponse.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

HttpClient::HttpClient()
{
    handle = curl_easy_init();
    if(!handle) {
        printf("curl_easy_init() failed!");
    }
}

size_t HttpClient::invoke_write_data(void *ptr, size_t size, size_t nmemb, std::string* data)
{
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

HttpResponse * HttpClient::get(const char *url) {
    CURLcode res;
    std::string readBuffer;
    
    CURL* handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, HttpClient::invoke_write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(handle);

    return new HttpResponse(200, readBuffer);
}

HttpResponse * HttpClient::post(const char *url, const char* data) {
    CURLcode res;
    struct curl_slist *headers = NULL;
    std::string readBuffer;
    
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, HttpClient::invoke_write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &readBuffer);
    
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);
    
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data);
    
    res = curl_easy_perform(handle);
    curl_slist_free_all(headers);
    return new HttpResponse(200, readBuffer);
}

HttpResponse * HttpClient::put(const char *url, const char* data) {
    CURLcode res;
    struct curl_slist *headers = NULL;
    std::string readBuffer;
    
    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, HttpClient::invoke_write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &readBuffer);
    
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data);
    
    res = curl_easy_perform(handle);
    curl_slist_free_all(headers);

    return new HttpResponse(200, readBuffer);
}