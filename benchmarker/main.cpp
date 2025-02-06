#include <unordered_map>

#include "Benchmark.hpp"
#include "Result.hpp"
#include "Test.hpp"
#include "../hasherLib/int_hashers.hpp"
#include "../hasherLib/string_hashers.hpp"

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

    auto ump4 = new map<int, int, hash_int>();
    std::vector<int> veee;
    std::vector<int> veve;
    std::vector<int> vuvu;
    ump4->insert({1, 1});
    veee.push_back(1);
    veve.push_back(2);
    ump4->insert({4,1});
    vuvu.push_back(4);
    TestScenario<map<int, int, hash_int>, int, int> scenario(ump4, std::move(veee), std::move(veve), std::move(vuvu),"habanero test");
    bch.addTest(&scenario);




    bch.addTest(&remove_test);
    bch.addTest(&rmTest);
    bch.addTest(&test);
    auto ress = bch.run();
    for(auto var : ress) {
        var.printAvg();
    }
}
