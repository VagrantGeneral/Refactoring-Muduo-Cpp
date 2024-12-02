#include "Logger.h"

int main() {
    //std::cout << Timestamp::now().toString() << std::endl;
    LOG_INFO("fff %d", __LINE__);

    return 0;
}