#include "Result.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <utility>
#include <format>
#include <sstream>

Result::Result(size_t replications, std::string hasher, std::string type)
{
    hasher_ = std::move(hasher);
    type_ = std::move(type);
    measurements_ = new std::map<std::string, std::vector<nano_t>>();
    replications_ = replications;
    keys_ = new std::vector<std::string>();
}

void Result::writeToFile() {
    const time_t now = std::time(nullptr);
    const std::string dataName = now + "data.csv";
    std::string metadataName = now + "metadata.json";
    writeCsv(dataName);
    writeJson(metadataName);
}

void Result::addKey(const std::string &testName) const {
    keys_->push_back(testName);
}

void Result::addRecord(const std::string &testName, nano_t record) const {
    (*measurements_)[testName].push_back(record);
}

void Result::writeCsv(const std::string &path) const {
    std::fstream file;
    file.open(path);
    file << "replications;";
    for (size_t i = 0; i < keys_->size(); ++i) {
        file << (*keys_)[i];
        if (i < keys_->size() - 1) {
            file << ";";
        }
    }
    file << std::endl;
    for (size_t i = 0; i < replications_; ++i) {
        file << i + 1 << ";";
        for (size_t j = 0; j < keys_->size(); ++j) {
            file << (*measurements_)[(*keys_)[j]][i];
            if (j < keys_->size() - 1) {
                file << ";";
            }
        }
        file << std::endl;
    }
    file.close();
}

void Result::writeJson(const std::string &path) {
    std::fstream file;
    file.open(path);
    std::stringstream jsonSteam;
    jsonSteam << "{\n  \"keyType\": \"" << type_ << "\",\n  \"hashType\": \"" << hasher_ << "\"\n}";
    file << jsonSteam.str();
    file.close();
}

std::string Result::serveData() {
    std::string result = name_ + "\n";

        return result;
}

Result::~Result() {
    delete measurements_;
}

