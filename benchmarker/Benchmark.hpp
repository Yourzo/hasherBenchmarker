#pragma once
#include <string>
#include <vector>
#include <chrono>

#include "Test.hpp"
#include "Result.hpp"

using nano_t = std::chrono::nanoseconds;

class Benchmark {
public:
    Benchmark(std::string name, const std::vector<size_t> &sizes, size_t replications);
    void addTest(TestBase *test);
    Result *run();
    ~Benchmark() = default;

private:
    void printProgresBar(size_t count, double index);

    std::vector<TestBase *> tests_{};
    size_t replications_; //this
    std::string name_;
};
