#include "Result.hpp"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

Result::Result(const size_t replications)
{
    measurements_ = new std::map<std::string, std::vector<nano_t>>();
    replications_ = replications;
    testNames_ = new std::vector<std::string>();
}

void Result::writeToFile() const {
    const time_t now = std::time(nullptr);
    std::filesystem::path currPath = std::filesystem::current_path();
    create_directories(currPath.append("results"));

    std::filesystem::path dataName(currPath);
    dataName /= (std::to_string(now) + ".data.csv");
    std::filesystem::path metadataName(currPath);
    metadataName /= (std::to_string(now) + ".metadata.json");

    writeCsv(dataName);
    writeJson(metadataName);
}

void Result::addTest(const std::string &testName, const std::string& keyTypeName, const std::string& hasherName) {
    testNames_->push_back(testName);
    metadata_.emplace(testName, ResultMetadata(hasherName, keyTypeName));
}

void Result::addRecord(const std::string &testName, const nano_t record) {
    (*measurements_)[testName].push_back(record);
}

void Result::writeCsv(const std::string &path) const {
    std::ofstream file;
    file.open(path);
    file << "replications;";
    for (size_t i = 0; i < testNames_->size(); ++i) {
        file << (*testNames_)[i];
        if (i != testNames_->size() - 1) {
            file << ";";
        }
    }
    file << std::endl;
    for (size_t i = 0; i < replications_; ++i) {
        file << i + 1 << ";";
        for (size_t j = 0; j < testNames_->size(); ++j) {
            file << (*measurements_)[(*testNames_)[j]][i];
            if (j != testNames_->size() - 1) {
                file << ";";
            }
        }
        file << std::endl;
    }
    file.close();
}

void Result::writeJson(const std::string &path) const {
    std::ofstream file(path);
    std::stringstream jsonSteam;
    jsonSteam << "{ \"hashers\": [";
    for (size_t i = 0; i < testNames_->size(); ++i) {
        jsonSteam << "{\"keyType\": \"" << metadata_.find(testNames_->at(i))->second.keyTypeName_ <<
            "\",  \"hashType\": \"" << metadata_.find(testNames_->at(i))->second.hasherName_ << "\"}";
    }
    jsonSteam << "] }";
    file << jsonSteam.str();
    file.close();
}

Result::~Result() {
    delete measurements_;
}
