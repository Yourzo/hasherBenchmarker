#include "Benchmark.hpp"

#include <iostream>

Benchmark::Benchmark(std::string name, size_t size,
                     const size_t replications, const bool shuffle) :
    name_(std::move(name)) {
    tests_.reserve(size);
    replications_ = replications;
    shuffle_ = shuffle;
}

void Benchmark::addTest(TestBase* test) { tests_.push_back(test); }

Result* Benchmark::run() {
    auto* result = new Result(replications_);
    const double size = tests_.size() * replications_;
    size_t count = 0;
    for (TestBase* test: tests_) {
        result->addTest(test->getName(), test->getDescriptor());
        for (size_t i = 0; i < replications_; ++i) {
            if (shuffle_) {
                test->shuffleKeys();
            }
            auto start = std::chrono::high_resolution_clock::now();
            test->execute();
            auto end = std::chrono::high_resolution_clock::now();
            result->addRecord(test->getName(),
                              std::chrono::duration_cast<nano_t>(
                                      (end - start) / test->getMapSize()));
            ++count;
            printProgresBar(count, size);
        }
    }
    return result;
}

Benchmark::~Benchmark() {
    for (const TestBase* test: tests_) {
        delete test;
    }
}

void Benchmark::printProgresBar(const size_t count, const double size) {
    double progress = count / size;
    double position = 50 * progress;
    std::string bar = "[";
    for (size_t i = 0; i < 50; ++i) {
        if (i < position) {
            bar.append("=");
        } else {
            bar.append(" ");
        }
    }
    bar.append("] ");
    std::cout << bar << static_cast<int>(progress * 100.0) << " %\r";
    std::cout.flush();
    if (progress == 1) {
        std::cout << std::endl;
    }
}
