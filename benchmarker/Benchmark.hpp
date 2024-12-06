#pragma once
#include <string>
#include <vector>
#include <chrono>

#include "Test.hpp"
#include "Result.hpp"

using nano_t = std::chrono::nanoseconds;

class Benchmark {
public:
    Benchmark(std::string name, size_t size);
    void addTest(TestBase *test);
    std::vector<Result> run();
    ~Benchmark();

private:
    std::vector<TestBase*> tests_{};
    std::string name_;
};
