#include "EPollPoller.h"
#include "Poller.h"

const int KNew = -1;
const int KAdded = 1;
const int KDeleted = 2;

EPollPoller::EPollPoller(EventLoop* loop) 
    : Poller(loop)
    , epollfd_(::epoll_create1(EPOLL_CLOEXEC))
    , events_(KInitEventListSize) {
    //
    if (epollfd_ < 0) {
        LOG_FATAL("epoll_create error : %d \n", errno);
    }

}

EPollPoller::~EPollPoller() {
    ::close(epollfd_);
}

Timestamp EPollPoller::poll(int timeoutMs, ChannelList* activeChannels) {

}

void EPollPoller::updateChannel(Channel* channel) {
    
}

void EPollPoller::removeChannel(Channel* channel) {
    
}

void fillActiveChannels(int numEvents, ChannelList* activeChannels) {

}

void EPollPoller::update(int operation, Channel* channel) {

}