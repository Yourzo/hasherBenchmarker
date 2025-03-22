#pragma once

#include "Benchmark.hpp"

class BenchmarkFactory {
    public:
        static Benchmark*
        createBenchmark(const std::vector<std::string>& types,
                        const std::vector<std::string>& hashers,
                        const std::vector<std::string>& generators,
                        size_t replications,
                        const std::vector<size_t>& mapSizes, bool shuffle);

    private:
        static TestBase* createTest(const TestDescriptor& descriptor);
        static void load(size_t done, size_t count);
};
