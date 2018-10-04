#pragma once

#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include "mdns.h"

class MdnsHelper
{
    public:
        char* discover();
        static char result[100];
        static bool hasResult;
    protected:
        mdns_string_t ipv4_address_to_string(char* buffer, size_t capacity, const struct sockaddr_in* addr);
        mdns_string_t ip_address_to_string(char* buffer, size_t capacity, const struct sockaddr* addr);
        static int mdns_calback(const struct sockaddr* from, mdns_entry_type_t entry, uint16_t type, uint16_t rclass, uint32_t ttl, const void* data, size_t size, size_t offset, size_t length);
};