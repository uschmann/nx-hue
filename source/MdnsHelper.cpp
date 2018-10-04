#include "MdnsHelper.h"

char MdnsHelper::result[100];
bool MdnsHelper::hasResult = false;

mdns_string_t MdnsHelper::ip_address_to_string(char* buffer, size_t capacity, const struct sockaddr* addr) {
    return ipv4_address_to_string(buffer, capacity, (const struct sockaddr_in*)addr);
}

mdns_string_t MdnsHelper::ipv4_address_to_string(char* buffer, size_t capacity, const struct sockaddr_in* addr) {
    char host[NI_MAXHOST] = {0};
    char service[NI_MAXSERV] = {0};
    int ret = getnameinfo((const struct sockaddr*)addr, sizeof(struct sockaddr_in),
                          host, NI_MAXHOST, service, NI_MAXSERV,
                          NI_NUMERICSERV | NI_NUMERICHOST);
    int len = 0;
    if (ret == 0) {
        if (addr->sin_port != 0)
            len = snprintf(buffer, capacity, "%s:%s", host, service);
        else
            len = snprintf(buffer, capacity, "%s", host);
    }
    if (len >= capacity)
        len = (int)capacity - 1;
    mdns_string_t str = {buffer, (size_t)len};
    return str;
}

int MdnsHelper::mdns_calback(const struct sockaddr* from,
         mdns_entry_type_t entry, uint16_t type,
         uint16_t rclass, uint32_t ttl,
         const void* data, size_t size, size_t offset, size_t length) {
    
	struct sockaddr_in *ipv4 = (struct sockaddr_in *)from;
	char addrbuffer[64];

	inet_ntop(AF_INET, &(ipv4->sin_addr), addrbuffer, INET_ADDRSTRLEN);
    sprintf(MdnsHelper::result, "%s", addrbuffer);

    MdnsHelper::hasResult = true;

    return 0;
}

char* MdnsHelper::discover()
{
	size_t capacity = 2048;
    void* buffer = 0;

    int sock = mdns_socket_open_ipv4();
    if (sock < 0) {
        printf("Failed to open socket: %s\n", strerror(errno));
        return NULL;
    }
    printf("Opened IPv4 socket for mDNS/DNS-SD\n");

	buffer = malloc(capacity);
    printf("Sending mDNS query\n");
    if (mdns_query_send(sock, MDNS_RECORDTYPE_PTR,
                        MDNS_STRING_CONST("_hue._tcp.local."),
                        buffer, capacity)) {
        printf("Failed to send mDNS query: %s\n", strerror(errno));
		return  NULL;
    }

	sleep(1);
    mdns_query_recv(sock, buffer, capacity, MdnsHelper::mdns_calback);

	free(buffer);
	mdns_socket_close(sock);

	return MdnsHelper::hasResult ? MdnsHelper::result : NULL;
}