#pragma once

#include "Benchmark.hpp"
#include <functional>

class BenchmarkFactory {
public:
    static Benchmark* createBenchmark(const std::vector<std::string> &types, const std::vector<std::string> &hashers, const std::vector<std::string> &
                                      generators,
                                      size_t replications, const std::vector<size_t> &mapSizes);
private:
    static TestBase* createTest(const TestDescriptor &descriptor);
};
