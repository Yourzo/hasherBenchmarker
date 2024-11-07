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

    auto ump2 = new std::unordered_map<int, int>();
    auto ve2 = new std::vector<int>();
    ve2->push_back(1);
    LookupTest<std::unordered_map<int, int>, int, int> rmTest(ump2, ve2);
    ump2->insert({1, 1});
    rmTest.before();
    auto start2 = std::chrono::high_resolution_clock::now();
    rmTest.execute();
    auto end2 = std::chrono::high_resolution_clock::now();
    rmTest.after();
    auto elapsed_time2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);
    std::cout << elapsed_time2.count() << std::endl;
}
