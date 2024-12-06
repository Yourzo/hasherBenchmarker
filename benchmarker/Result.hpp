#pragma once

#include <chrono>

using nano_t = std::chrono::nanoseconds;

class Result{
public:
    Result(std::string name, size_t recordCount);

    void addRecord(nano_t record);

private:
    std::vector<nano_t> measurements_;
    std::string name_;
};

