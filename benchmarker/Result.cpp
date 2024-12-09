#include "Result.hpp"
#include <iostream>

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

    std::cout << name_;
    std::cout << ":   average operation time:" << avg << std::endl;
}

void Result::outToCSV(const std::string &path) {

}

void Result::addRecord(const nano_t record) {
    measurements_.push_back(record);
}
