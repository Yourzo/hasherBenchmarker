#include "Benchmark.hpp"

#include <iostream>


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
    double size = tests_.size() * replications_;
    size_t count = 0;
    for (TestBase* test: tests_) {
        result->addTest(test->getName(), test->getTypeName(), test->getHasherName());
        for (size_t i = 0; i < replications_; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            test->execute();
            auto end = std::chrono::high_resolution_clock::now();
            result->addRecord(test->getName(), std::chrono::duration_cast<nano_t>((end - start) / test->getSize()));
            ++count;
            printProgresBar(count, size);
        }
    }
    return result;
}

void Benchmark::printProgresBar(size_t count, double size) {
    double progress = count / size;
    double position = 50 * progress;
    std::string bar ="[";
    for (size_t i = 0; i < 50; ++i) {
        if (i < position) {
            bar.append("=");
        } else {
            bar.append(" ");
        }
    }
    bar.append("] ");
    std::cout << bar << static_cast<int>(progress * 100.0) << " %\r";
}
