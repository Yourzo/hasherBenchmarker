#pragma once
#include <string>
#include <utility>
#include <vector>

#include "Test.hpp"


template<typename Map, typename K, typename E>
class Benchmark {
public:
    Benchmark(std::string name, size_t size);
    Benchmark(Benchmark &&) = default;
    Benchmark(const Benchmark &) = default;
    Benchmark &operator=(Benchmark &&) = default;
    Benchmark &operator=(const Benchmark &) = default;
    void addTest(const Test<Map, K, E> &&test);
    size_t execute();
    ~Benchmark();

private:
    std::vector<Test<Map, K, E>> tests_; 
    std::string name_;
};

template<typename Map, typename K, typename E>
Benchmark<Map, K, E>::Benchmark(std::string name, size_t size):
name_(std::move(name)), tests_(size) {};

template<typename Map, typename K, typename E>
void Benchmark<Map, K, E>::addTest(const Test<Map, K, E> &&test) {
    tests_.push_back(test);
}

template<typename Map, typename K, typename E>
size_t Benchmark<Map, K, E>::execute() {
    return -1;
}

template<typename Map, typename K, typename E>
Benchmark<Map, K, E>::~Benchmark() {
}

