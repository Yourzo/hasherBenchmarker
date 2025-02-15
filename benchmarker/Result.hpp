#pragma once

#include <chrono>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using nano_t = std::chrono::nanoseconds;

struct ResultMetadata {
    std::string generatorName_;
    std::string hasherName_;
    std::string keyTypeName_;
};

class Result{
public:
    explicit Result(size_t replications, size_t mapSize);
    void outPutRecs();
    void printAvg();
    void writeToFile() const;
    void addTest(const std::string &testName, const std::string &keyTypeName,
                 const std::string &hasherName, const std::string &generatorName);
    void addRecord(const std::string &testName, nano_t record);
    ~Result();

private:
    std::map<std::string, std::vector<nano_t>>* measurements_;
    std::vector<std::string>* testNames_;
    std::unordered_map<std::string, ResultMetadata> metadata_;
    size_t replications_;
    size_t mapSize_;
    void writeCsv(const std::string &path) const;
    void writeJson(const std::string &path) const;
    std::string serveData();
};
