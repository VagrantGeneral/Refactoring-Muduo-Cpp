#include "Poller.h"

Poller::Poller(EventLoop* loop) : ownerLoop_(loop) {
    //poller
}

bool Poller::hasChannel(Channel* channel) const {
    ChannelMap::const_iterator iter = channels_.find(channel->fd());
    if (iter != channels_.end() && iter->second == channel) {
        return true;
    }
    return false;
}



// 这个静态函数的作用是返回一个具体的poller，不是pollpoller就是epollpoller
// 这样就需要包含PollPoller.h和EpollPoller.h
// 这样是很不好的，因此我们必须在继承完之后定义它
// Poller* Poller::newDefaultPoller(EventLoop* loop) {
//
// }
