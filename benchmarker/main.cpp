#include <unordered_map>

#include "Benchmark.hpp"
#include "Result.hpp"
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
    LookupTest<map<std::string, int, jenkins_hash>, std::string, int> test(ump, std::move(ve), "haha");

    auto ump2 = new map<int, int, hash_int>();
    std::vector<int> ve2;
    ve2.push_back(1);
    LookupTest<map<int, int, hash_int>, int, int> rmTest(ump2, (std::move(ve2)), "hehe");
    ump2->insert({1, 1});

    auto ump3 = new map<int, int, hash_int2>();
    std::vector<int> ve3;
    ump3->insert({1, 1});
    ve3.push_back(1);
    RemoveTest<map<int, int, hash_int2>, int, int> remove_test(ump3, (std::move(ve3)), "haha");
    Benchmark bch("TEST", 3);
    bch.addTest(&remove_test);
    bch.addTest(&rmTest);
    bch.addTest(&test);
    auto ress = bch.run();
    for(auto var : ress) {
        var.printAvg();
    }
}
