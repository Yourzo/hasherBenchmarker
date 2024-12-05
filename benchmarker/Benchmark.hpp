#pragma once
#include <string>
#include <vector>
#include <chrono>

#include "Test.hpp"

using nano_t = std::chrono::nanoseconds;

class Benchmark {
public:
    Benchmark(std::string name, size_t size);
    void addTest(const TestBase *test);
    std::vector<std::vector<nano_t>> run();
    ~Benchmark();

private:
    std::vector<Test*> tests_{};
    std::string name_;
};
