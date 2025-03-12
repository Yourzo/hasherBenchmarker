#include "Result.hpp"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Result::Result(const size_t replications) { replications_ = replications; }

void Result::writeToFile() {
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

void Result::addTest(const std::string& testName, TestDescriptor& testDataPtr) {
    testNames_.push_back(testName);
    metadata_.emplace(testName, testDataPtr);
}

void Result::addRecord(const std::string& testName, const nano_t record) {
    measurements_[testName].push_back(record);
}

void Result::writeCsv(const std::string& path) {
    std::ofstream file;
    file.open(path);
    file << "replications;";
    for (size_t i = 0; i < testNames_.size(); ++i) {
        file << testNames_[i];
        if (i != testNames_.size() - 1) {
            file << ";";
        }
    }
    file << std::endl;
    for (size_t i = 0; i < replications_; ++i) {
        file << i + 1 << ";";
        for (size_t j = 0; j < testNames_.size(); ++j) {
            file << measurements_[testNames_[j]][i];
            if (j != testNames_.size() - 1) {
                file << ";";
            }
        }
        file << std::endl;
    }
    file.close();
}

void Result::writeJson(const std::string& path) const {
    json j;
    j["replications"] = replications_;
    j["hashers"] = json::array();

    for (const auto& testName: testNames_) {
        const auto& [name, generatorName, hasherName, mapSize] =
                metadata_.at(testName);
        j["hashers"].push_back({{"name", testName},
                                {"map size", mapSize},
                                {"generator", generatorName},
                                {"hashType", hasherName}});
    }

    if (std::ofstream file(path); file.is_open()) {
        file << j.dump(4);
        file.close();
    }
}
