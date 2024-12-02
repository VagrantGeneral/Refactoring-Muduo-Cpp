#include "InetAddress.h"

InetAddress::InetAddress(uint16_t port, std::string ip) {
    bzero(&addr_, sizeof(addr_));

    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}

std::string InetAddress::toIP() const {
    char buff[64] = {0};
    
    ::inet_ntop(AF_INET, &addr_.sin_addr, buff, sizeof(buff));
    return buff;
}

std::string InetAddress::toIPPORT() const {
    char buff[64] = {0};

    ::inet_ntop(AF_INET, &addr_.sin_addr, buff, sizeof(buff));
    size_t end = strlen(buff);

    uint16_t port = ntohs(addr_.sin_port);

    sprintf(buff + end, " : %u", port);
    return buff;
}

uint16_t InetAddress::toPORT() const {
    return ntohs(addr_.sin_port);
}