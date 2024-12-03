#pragma once

#include "noncopyable.h"
#include "Channel.h"
#include "Timestamp.h"
#include "Logger.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include <sys/epoll.h>

class Channel;
class EventLoop;

class Poller : noncopyable{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop* loop);

    virtual ~Poller() = default;

    //为所有的IO复用保留统一的接口
    virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels) = 0;

    virtual void updateChannel(Channel* channel) = 0;

    virtual void removeChannel(Channel* channel) = 0;

public:
    bool hasChannel(Channel* channel) const;

    //获取默认的Poller对象
    static Poller* newDefaultPoller(EventLoop* loop);

protected:
    using ChannelMap = std::unordered_map<int, Channel*>;

    ChannelMap channels_;

private:
    EventLoop* ownerLoop_;
};