#pragma once

#include "Benchmark.hpp"
#include <unordered_map>
#include <functional>
#include "../hasherLib/hasherUtils.hpp"

class BenchmarkFactory {
public:
    static Benchmark* createBenchmark(const std::vector<std::string> &types, const std::vector<std::string> &hashers, const std::vector<std::string> &
                                      generators,
                                      size_t replications, const std::vector<size_t> &mapSizes);
    static void initialize();
private:
    static std::unordered_map<std::string, BaseHasher*> hashers_;
    static TestBase* createTest(const std::string &type, const std::string &name, const std::string &hasher, size_t size, const std::string &generator);
};
