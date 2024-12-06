#include "Benchmark.hpp"

Benchmark::Benchmark(std::string name, size_t size):
tests_(size), name_(std::move(name)) {}

void Benchmark::addTest(TestBase *test) {
    tests_.push_back(test);
}

std::vector<Result> Benchmark::run() {
    std::vector<Result> results{};
    for (TestBase* test: tests_) {
        results.emplace_back(test->getName(), test->getSize());
        for (size_t i = 0; i < test->getSize(); ++i) {
            test->before();
            auto start = std::chrono::high_resolution_clock::now();
            test->execute();
            auto end = std::chrono::high_resolution_clock::now();
            test->after();
            results.back().addRecord(std::chrono::duration_cast<nano_t>(end - start));
        }
    }
    return results;
}
