#include "Result.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

Result::Result(std::string name, const size_t recordCount): name_(std::move(name))
{
    measurements_.reserve(recordCount);
}

void Result::printAvg() {
    nano_t sum = {};
    for (const auto data: measurements_) {
        sum += data;
    }
    nano_t avg = sum / measurements_.size();
    std::cout << name_ << " avg operation time: " << avg << std::endl;
}

void Result::outToCSV(const std::string &path) {
    std::fstream _file(path);
    if (!_file.is_open()) {
        throw std::runtime_error("hehe");
    }
}

void Result::addRecord(const nano_t record) {
    measurements_.push_back(record);
}

std::string Result::serveData() {
    std::string result = name_ + "\n";

        return result;
}
