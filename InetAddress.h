#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <strings.h>

//封装socket的地址类型
class InetAddress {
public:
    InetAddress(uint16_t port, std::string ip = "127.0.0.1");

    InetAddress(const sockaddr_in& addr) : addr_(addr) { /**/ }

public:
    std::string toIP() const;

    std::string toIPPORT() const;

    uint16_t toPORT() const;

    const sockaddr_in* getSockAddr() const { return &addr_;}

private:
    sockaddr_in addr_;
};