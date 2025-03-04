#pragma once

#include <chrono>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "Test.hpp"

using nano_t = std::chrono::nanoseconds;

class Result{
public:
    explicit Result(size_t replications);
    void outPutRecs();
    void printAvg();
    void writeToFile() const;
    void addTest(const std::string &testName, TestDescriptor &testDataPtr);
    void addRecord(const std::string &testName, nano_t record);
    ~Result();

private:
    std::map<std::string, std::vector<nano_t>>* measurements_;
    std::vector<std::string>* testNames_;
    std::unordered_map<std::string, TestDescriptor> metadata_;
    size_t replications_;
    void writeCsv(const std::string &path) const;
    void writeJson(const std::string &path) const;
    std::string serveData();
};
