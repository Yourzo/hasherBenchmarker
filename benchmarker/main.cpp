#include <iostream>
#include <unordered_map>
#include <chrono>
#include "Test.hpp"
#include "../hasherLib/int_hashers.cpp"
#include "../hasherLib/string_hashers.cpp"

template<typename K, typename T, typename H>
using map = std::unordered_map<K, T, H>;

int main()
{
    auto ump = new map<std::string, int, jenkins_hash>();
    std::vector<std::string> ve;
    ump->insert({"hehe", 1});
    ve.emplace_back("hehe");
    LookupTest<map<std::string, int, jenkins_hash>, std::string, int> test(ump, std::move(ve));
    std::cout << test.getMapSize();
    test.before();
    auto start = std::chrono::high_resolution_clock::now();
    test.execute();
    auto end = std::chrono::high_resolution_clock::now();
    test.after();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << elapsed_time.count() << std::endl;

    auto ump2 = new map<int, int, hash_int>();
    std::vector<int> ve2;
    ve2.push_back(1);
    LookupTest<map<int, int, hash_int>, int, int> rmTest(ump2, (std::move(ve2)));
    ump2->insert({1, 1});
    rmTest.before();
    auto start2 = std::chrono::high_resolution_clock::now();
    rmTest.execute();
    auto end2 = std::chrono::high_resolution_clock::now();
    rmTest.after();
    auto elapsed_time2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);
    std::cout << elapsed_time2.count() << std::endl;

    auto ump3 = new map<int, int, hash_int2>();
    std::vector<int> ve3;
    ump3->insert({1, 1});
    ve3.push_back(1);
    RemoveTest<map<int, int, hash_int2>, int, int> remove_test(ump3, (std::move(ve3)));
    remove_test.before();
    auto start3 = std::chrono::high_resolution_clock::now();
    remove_test.execute();
    auto end3 = std::chrono::high_resolution_clock::now();
    remove_test.after();
    auto elapsed_time3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3);
    std::cout << elapsed_time3.count() << std::endl;
}
