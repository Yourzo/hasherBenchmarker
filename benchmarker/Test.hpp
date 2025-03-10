#pragma once

#include <string>
#include <utility>
#include <vector>

struct TestDescriptor {
    std::string name_;
    std::string generator_;
    std::string hasher_;
    size_t mapSize_;
};

class TestBase {
public:
    virtual void execute() = 0;
    virtual std::string getName() = 0;
    virtual size_t getMapSize() = 0;
    virtual TestDescriptor& getDescriptor() = 0;
    virtual ~TestBase() = default;
};

template<typename Map, typename K, typename Gen>
class Test: public TestBase
{
protected:
    Map map_;
    std::vector<K> keys_;
    TestDescriptor metadata_;
public:
    Test(Gen generator, TestDescriptor data);
    std::string getName() override;
    void execute() override;
    size_t getMapSize() override;
    TestDescriptor& getDescriptor() override;
};

template<typename Map, typename K, typename Gen>
Test<Map, K, Gen>::Test(Gen generator, TestDescriptor data) {
    keys_ = (*generator)(data.mapSize_);
    for (size_t i = 0; i < keys_.size(); ++i) {
        map_[keys_[i]] = 0;
    }
    metadata_ = std::move(data);
}

template<typename Map, typename K, typename Gen>
std::string Test<Map, K, Gen>::getName() {
    return metadata_.name_;
}

/**
 * looks up keys provided in construction
 */
template<typename Map, typename K, typename Gen>
void Test<Map, K, Gen>::execute() {
    for (K key : keys_) {
        map_.contains(key);
    }
}

template<typename Map, typename K, typename Gen>
size_t Test<Map, K, Gen>::getMapSize() {
    return map_.size();
}

template<typename Map, typename K, typename Gen>
TestDescriptor& Test<Map, K, Gen>::getDescriptor() {
    return metadata_;
}
