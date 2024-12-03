#include "Poller.h"

#include <stdlib.h>

Poller* Poller::newDefaultPoller(EventLoop* loop) {
    //根据环境变量返回poll或epoll
    if (::getenv("MUDUO_USE_POLL")) {
        return nullptr;//poll
    }
    else {
        return nullptr;//epoll
    }
}
