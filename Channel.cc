#include "Channel.h"

const int Channel::KNoneEvent = 0;
const int Channel::KReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::KWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop* loop, int fd) 
    : loop_(loop)
    , fd_(fd) 
    , events_(0)
    , revents_(0)
    , index_(-1)
    , tied_(false) {
    /**/
}

Channel::~Channel() { 
    //
}

// 事件处理
void Channel::handleEvent(Timestamp receiveTime) {   
    std::shared_ptr<void> guard;
    if (tied_) {
        guard = tie_.lock();
        if (guard) {
            handleEventWithGuard(receiveTime);
        }
    }
    else {
        handleEventWithGuard(receiveTime);
    }
}

void Channel::tie(const std::shared_ptr<void>& obj) {
    tie_ = obj;
    tied_ = true;
}

// 在Channel所属的EventLoop中删除掉。
void Channel::remove() {
    //loop_->removeChannel(this);
}

// 在Channel所属的EventLoop中更新自己的事件状态。另一种epoll_ctl的表现
void Channel::update() {
    //loop_->updateChannel(this);
}

//根据实际发生的事件调用对应回调操作
void Channel::handleEventWithGuard(Timestamp receiveTime) {
    LOG_INFO("Channel handleEvent revents : %d\n", revents_);

    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        if (closeCallback_) {
            closeCallback_();
        }
    }

    if (revents_ & EPOLLERR) {
        if (errorCallback_) {
            errorCallback_();
        }
    } 

    if (revents_ & (EPOLLIN | EPOLLPRI)) {
        if (readCallback_) {
            readCallback_(receiveTime);
        }
    }

    if (revents_ & EPOLLOUT) {
        if (writeCallback_) {
            writeCallback_();
        }
    } 
}
