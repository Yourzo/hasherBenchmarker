#include "Benchmark.hpp"


Benchmark::Benchmark(std::string name, size_t size, size_t replications):
name_(std::move(name)) {
    tests_.reserve(size);
    replications_ = replications;
}

void Benchmark::addTest(TestBase *test) {
    tests_.push_back(test);
}

Result* Benchmark::run() {
    auto* result = new Result(replications_);
    for (TestBase* test: tests_) {
        result->addTest(test->getName(), test->getTypeName(), test->getHasherName());
        for (size_t i = 0; i < replications_; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            test->execute();
            auto end = std::chrono::high_resolution_clock::now();
            result->addRecord(test->getName(), std::chrono::duration_cast<nano_t>((end - start) / test->getSize()));
        }
    }
    return result;
}
