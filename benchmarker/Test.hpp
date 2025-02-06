#pragma once

#include <utility>
#include <vector>
#include <string>

#include "Test.hpp"

class TestBase {
public:
    virtual void execute() = 0;
    virtual void execute(bool onGiven) = 0;
    virtual size_t getSize() = 0;
    virtual std::string getName() = 0;
    virtual ~TestBase() = default;
};

template<typename Map, typename K, typename E>
class Test: public TestBase
{
protected:
    Map* map_;
    std::vector<K> keys_;
    std::string name_;
public:
    Test(Map *map, std::string name, std::vector<K>&& keys);
    std::string getName() override;
    void execute() override;
    void execute(bool onGiven) override;
    size_t getSize() override;
    ~Test() override;
};

/**
 * @param map benchmarked map
 * @param name of the test
 * @param keys keys to lookup in map
 */
template<typename Map, typename K, typename E>
Test<Map, K, E>::Test(Map *map, std::string name, std::vector<K>&& keys) {
    map_ = map;
    keys_ = std::move(keys);
    name_ = std::move(name);
}

template<typename Map, typename K, typename E>
std::string Test<Map, K, E>::getName() {
    return name_;
}

/**
 * looks up every key contained in map
 */
template<typename Map, typename K, typename E>
void Test<Map, K, E>::execute() {
    for (auto const& [key, _] : map_) {
        map_->contains(key);
    }
}

/**
 * looks up keys provided in construction
 */
template<typename Map, typename K, typename E>
void Test<Map, K, E>::execute(bool onGiven) {
    for (K key : keys_) {
        map_->contains(key);
    }
}

template<typename Map, typename K, typename E>
size_t Test<Map, K, E>::getSize() {
    return map_->size();
}

template<typename Map, typename K, typename E>
Test<Map, K, E>::~Test() {
    delete map_;
}
