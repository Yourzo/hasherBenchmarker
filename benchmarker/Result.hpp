#pragma once

#include <chrono>
#include <map>
#include <string>
#include <vector>

using nano_t = std::chrono::nanoseconds;

class Result{
public:
    explicit Result(size_t replications, std::string hasher, std::string type);
    void outPutRecs();
    void printAvg();
    void writeToFile() const;
    void addKey(const std::string &testName) const;
    void addRecord(const std::string &testName, nano_t record) const;
    ~Result();

private:
    std::map<std::string, std::vector<nano_t>>* measurements_;
    std::vector<std::string>* keys_;
    std::string name_;
    std::string hasher_;
    std::string type_;
    size_t replications_;
    void writeCsv(const std::string &path) const;
    void writeJson(const std::string &path) const;//tested
    std::string serveData();
};
