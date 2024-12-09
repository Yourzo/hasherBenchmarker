#pragma once

#include <chrono>
#include <string>
#include <vector>

using nano_t = std::chrono::nanoseconds;

class Result{
public:
    Result(std::string name, size_t recordCount);
    void outPutRecs();
    void printAvg();
    void outToCSV(const std::string &path);
    void addRecord(nano_t record);

private:
    std::vector<nano_t> measurements_;
    std::string name_;
};

