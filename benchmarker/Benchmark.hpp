#pragma once
#include <chrono>
#include <string>
#include <vector>

#include "Result.hpp"
#include "Test.hpp"

using nano_t = std::chrono::nanoseconds;

class Benchmark {
    public:
        Benchmark(std::string name, const std::vector<size_t>& sizes,
                  size_t replications, bool shuffle);
        void addTest(TestBase* test);
        Result* run();
        ~Benchmark();

    private:
        void printProgresBar(size_t count, double index);
        std::vector<TestBase*> tests_{};
        size_t replications_;
        std::string name_;
        bool shuffle_;
};
