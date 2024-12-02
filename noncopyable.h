#pragma once

/*
noncopyable是一个功能性的类，当它被继承后，派生类对象将无法进行copy和赋值操作，只能进行构造和析构
*/
class noncopyable {
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};