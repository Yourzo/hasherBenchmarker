#include "Benchmark.hpp"

Benchmark::Benchmark(std::string name, size_t size):
tests_(size), name_(std::move(name)) {}

void Benchmark::addTest(const TestBase *test) {
    tests_.push_back(test);
}

std::vector<std::vector<nano_t>> Benchmark::run() {
    size_t index = 0;
    std::vector<std::vector<nano_t>> results(tests_.size());
    for (TestBase* test: tests_) {
        results[index].push_back(std::vector<std::chrono::nanoseconds>(test->getSize()));
        ++index;
        for (size_t i = 0; i < test->getSize(); ++i) {

            test->before();
            auto start = std::chrono::high_resolution_clock::now();
            test->execute();
            auto end = std::chrono::high_resolution_clock::now();
            test->after();
            results[i] = std::chrono::duration_cast<nano_t>(end - start);
        }
    }
    return results;
}
