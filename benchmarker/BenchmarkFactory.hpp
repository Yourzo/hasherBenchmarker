#pragma once

#include "Benchmark.hpp"

class BenchmarkFactory {
    public:
        static Benchmark* createBenchmark(const std::vector<TestDescriptor>& descs, size_t replications, bool shuffle);

    private:
        static TestBase* createTest(const TestDescriptor& descriptor);
        static void load(size_t done, size_t count);
};
