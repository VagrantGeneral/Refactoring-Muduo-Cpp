#pragma once

#include "noncopyable.h"
#include "Channel.h"
#include "Poller.h"
#include "Timestamp.h"
#include "Logger.h"

#include <iostream>
#include <memory>
#include <vector>
#include <sys/epoll.h>
#include <errno.h>

/*
* epoll的使用
* epoll_create 创建epfd
* epoll_ctl add/mod/del操作fd
* epoll_wait 监听
*/

class EPollPoller : public Poller {
public:
    EPollPoller(EventLoop* loop);

    ~EPollPoller() override;

    //重写基类的抽象方法
    Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;

    void updateChannel(Channel* channel) override;

    void removeChannel(Channel* channel) override;

public:


private:
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    void update(int operation, Channel* channel);

private:
    using EventList = std::vector<epoll_event>;

    static const int KInitEventListSize = 16;

    EventList events_; // epoll返回的事件集合
    
    int epollfd_; // epoll句柄

};