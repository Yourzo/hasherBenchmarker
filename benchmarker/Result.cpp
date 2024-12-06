#include "Result.hpp"

Result::Result(std::string name, const size_t recordCount) {
    name_ = std::move(name);
    measurements_.reserve(recordCount);
}

void Result::addRecord(const nano_t record) {
    measurements_.push_back(record);
}
