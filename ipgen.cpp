#include "ipgen.h"

uint32_t IPv4toUINT32(std::string IPv4)
{
    auto result = ntohl(inet_addr(IPv4.c_str()));
    return result;
}

std::string UINT32toIPv4(uint32_t IPv4)
{
    in_addr a;
    a.s_addr = htonl(IPv4);
    return std::string(inet_ntoa(a));
}

bool isValidIPv4(std::string IPv4)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, IPv4.c_str(), &(sa.sin_addr));
    return result == 1;
}
