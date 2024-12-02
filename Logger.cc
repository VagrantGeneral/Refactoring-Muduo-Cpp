#include "Logger.h"

//获取唯一实例
Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

//设置日志级别
void Logger::setLogLevel(int level) {
    logLevel_ = level;
}

//打印日志 [级别] time : msg
void Logger::log(std::string msg) {
    switch (logLevel_) {
    case INFO:
        std::cout << "[INFO]";
        break;
    case ERROR:
        std::cout << "[ERROR]";
        break;
    case FATAL:
        std::cout << "[FATAL]";
        break;
    case DEBUG:
        std::cout << "[DEBUG]";
        break;
    default:
        break;
    }
    
    //
    std::cout << Timestamp::now().toString() << " : " << msg << std::endl;
}

