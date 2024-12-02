#pragma once

#include <iostream>
#include <string>
#include <time.h>

class Timestamp {
public:
    Timestamp();

    Timestamp(int64_t microSecondsSinceEpoch);

public:
    static Timestamp now();

    std::string toString() const;

private:
    int64_t microSecondsSinceEpoch_;
};