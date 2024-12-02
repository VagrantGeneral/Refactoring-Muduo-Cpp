#pragma once

#include "noncopyable.h"
#include "Timestamp.h"
#include "EventLoop.h"
#include "Logger.h"

#include <iostream>
#include <functional>
#include <memory>
#include <sys/epoll.h>

class EventLoop;

/*
Channel 就是一个组合。在监听中，fd 经常会和它感兴趣的事件 event 在一起，不妨将它们以及对应的操作放在一起。
*/
class Channel : noncopyable {
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop* loop, int fd);

    ~Channel();

public:
    void handleEvent(Timestamp receiveTime);// 事件处理

    void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); } //读事件回调

    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); } //写事件回调

    void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); } //

    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

    void tie(const std::shared_ptr<void>& obj); //

    int fd() const { return fd_; }

    int events() const {return events_; }

    void set_revents(int revt) { revents_ = revt; }

    bool isNoneEvent() const { return events_ == KNoneEvent; }

    //
    void enableReading() { events_ |= KReadEvent; update(); }

    void disableReading() { events_ &= ~KReadEvent; update(); }
 
    void enableWriteing() { events_ |= KWriteEvent; update(); }

    void disableWriteing() { events_ &= ~KWriteEvent; update(); }

    void disableAll() {events_ = KNoneEvent; update(); }

    //实际发生的事件
    bool isNoneEvent() { return events_ == KNoneEvent; }

    bool isReadEvent() { return events_ == KReadEvent; }

    bool isWriteEvent() { return events_ == KWriteEvent; }

    //
    int index() { return index_; }

    void set_index(int idx) { index_ = idx; }

    //
    EventLoop* ownerLoop() { return loop_; }

    void remove();
    

private:
    void update();

    void handleEventWithGuard(Timestamp receiveTime);

    static const int KNoneEvent;
    static const int KReadEvent;
    static const int KWriteEvent;

    EventLoop* loop_; // 事件循环
    const int fd_; // 描述符
    int events_; // 注册的感兴趣的事件
    int revents_; // 实际发生的事件 
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;

    //为具体的事件设置回调
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};