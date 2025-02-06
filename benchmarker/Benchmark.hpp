#pragma once
#include <string>
#include <vector>
#include <chrono>

#include "Test.hpp"
#include "Result.hpp"

using nano_t = std::chrono::nanoseconds;

class Benchmark {
public:
    Benchmark(std::string name, size_t size, std::string hasherType, std::string keyType, size_t replications);
    void addTest(TestBase *test);
    Result* run();
    ~Benchmark() = default;

    //todo move values from test to here
private:
    std::vector<TestBase*> tests_{};
    size_t replications_;//this
    std::string keyType_;
    std::string hasherType_;
    std::string name_;
};
