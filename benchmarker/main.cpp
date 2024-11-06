#include <iostream>
#include <unordered_map>
#include <chrono>
#include "Test.hpp"

int main()
{
    auto ump = new std::unordered_map<std::string, int>();
    auto ve = new std::vector<std::string>();
    ump->insert({"hehe", 1});
    ve->push_back("hehe");
    LookupTest<std::unordered_map<std::string, int>, std::string, int> test(ump, ve);
    std::cout << test.getMapSize();
    test.before();
    auto start = std::chrono::high_resolution_clock::now();
    test.execute();
    auto end = std::chrono::high_resolution_clock::now();
    test.after();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << elapsed_time.count() << std::endl;
}
