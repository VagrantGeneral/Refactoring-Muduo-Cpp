#pragma once

#include "noncopyable.h"
#include "Timestamp.h"

#include <iostream>
#include <string>

//日志级别 INFO ERROR FATAL DEBUG
enum LogLevel {
    INFO, //信息
    ERROR, //错误
    FATAL, //致命
    DEBUG, //调试
};

//日志类
class Logger : private noncopyable {
public:
    //获取唯一实例
    static Logger& instance();

    //设置日志级别
    void setLogLevel(int Level);

    //打印日志
    void log(std::string msg);

private:
    Logger() {}

private:
    int logLevel_;
};


#define LOG_INFO(logmsgFormat, ...) \
    do { \
        Logger& logger = Logger::instance(); \
        logger.setLogLevel(INFO); \
        char buff[1024] = {0}; \
        snprintf(buff, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buff); \
    }\
    while (0);

#define LOG_ERROR(logmsgFormat, ...) \
    do { \
        Logger& logger = Logger::instance();\
        logger.setLogLevel(ERROR);\
        char buff[1024] = {0};\
        snprintf(buff, 1024, logmsgFormat, ##__VA_ARGS__);\
        logger.log(buff);\
    }\
    while (0);

#define LOG_FATAL(logmsgFormat, ...) \
    do { \
        Logger& logger = Logger::instance();\
        logger.setLogLevel(FATAL);\
        char buff[1024] = {0};\
        snprintf(buff, 1024, logmsgFormat, ##__VA_ARGS__);\
        logger.log(buff);\
        exit(-1);\
    }\
    while (0);

#ifdef MUDEBUG
#define LOG_DEBUG(logmsgFormat, ...) \
    do { \
        Logger& logger = Logger::instance();\
        logger.setLogLevel(DEBUG);\
        char buff[1024] = {0};\
        snprintf(buff, 1024, logmsgFormat, ##__VA_ARGS__);\
        logger.log(buff);\
    }\
    while (0);
#else
    #define LOG_DEBUG(logmsgFormat, ...)
#endif