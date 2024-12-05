#pragma once

#include <vector>

class TestBase {
public:
    virtual size_t getMapSize() = 0;
    virtual void after() = 0;
    virtual void execute() = 0;
    virtual void before() = 0;
    virtual size_t getSize() = 0;
    virtual ~TestBase();
};

template<typename Map>
class Test: public TestBase
{
protected:
    Map* map_;
public:
    explicit Test(Map *map);
    size_t getMapSize() override;
    ~Test() override;
};

template<typename Map, typename K, typename E>
class LookupTest : public Test<Map>
{
private:
    size_t index_ = 0;
protected:
    std::vector<K> keys_;
public:
    LookupTest(Map* map, std::vector<K> &&keys);
    void before() override;
    void execute() override;
    void after() override;
    size_t getSize() override;
    ~LookupTest() override = default;
};

template<typename Map, typename K, typename E>
class InsertTest : public Test<Map>
{
private:
    size_t index_ = 0;
protected:
    std::vector<K> keys_;
    E dummyVal_;
public:
    InsertTest(Map* map, std::vector<K> &&keys, E dummyVal);
    void before() override;
    void execute() override;
    void after() override;
    size_t getSize() override;
    ~InsertTest() override = default;
};

template<typename Map, typename K, typename E>
class RemoveTest : public Test<Map>
{
private:
    size_t index_ = 0;
protected:
    std::vector<K> keys_;
public:
    RemoveTest(Map* map, std::vector<K> &&keys);
    void before() override;
    void execute() override;
    void after() override;
    size_t getSize() override;
    ~RemoveTest() override = default;
};

template<typename Map>
Test<Map>::Test(Map *map)
{
    map_ = map;
}

template<typename Map>
Test<Map>::~Test()
{
    delete map_;
}

template<typename Map>
size_t Test<Map>::getMapSize()
{
    return map_->size();
}

template<typename Map, typename K, typename E>
LookupTest<Map, K, E>::LookupTest(Map* map, std::vector<K> &&keys):
Test<Map>(map), keys_(keys) {}


template<typename Map, typename K, typename E>
void LookupTest<Map, K, E>::before() {
    if (keys_.size() == index_)
        throw std::runtime_error("Out of bounds");
}

template<typename Map, typename K, typename E>
void LookupTest<Map, K, E>::execute() {
    this->map_->find(keys_.at(index_));
}

template<typename Map, typename K, typename E>
void LookupTest<Map, K, E>::after() {
    ++index_;
}

template<typename Map, typename K, typename E>
size_t LookupTest<Map, K, E>::getSize() {
    return keys_.size();
}

template<typename Map, typename K, typename E>
InsertTest<Map, K, E>::InsertTest(Map *map, std::vector<K> &&keys, E dummyVal):
Test<Map>(map), dummyVal_(dummyVal), keys_(keys) {}

template<typename Map, typename K, typename E>
void InsertTest<Map, K, E>::before() {
}

template<typename Map, typename K, typename E>
void InsertTest<Map, K, E>::execute() {
    this->map_->insert(keys_.at(index_), dummyVal_);
}

template<typename Map, typename K, typename E>
void InsertTest<Map, K, E>::after() {
    ++index_;
}

template<typename Map, typename K, typename E>
size_t InsertTest<Map, K, E>::getSize() {
    return keys_.size();
}

template<typename Map, typename K, typename E>
RemoveTest<Map, K, E>::RemoveTest(Map *map, std::vector<K> &&keys):
Test<Map>(map), keys_(keys) {}

template<typename Map, typename K, typename E>
void RemoveTest<Map, K, E>::before() {
}

template<typename Map, typename K, typename E>
void RemoveTest<Map, K, E>::execute() {
    this->map_->erase(keys_.at(index_));
}

template<typename Map, typename K, typename E>
void RemoveTest<Map, K, E>::after() {
    ++index_;
}

template<typename Map, typename K, typename E>
size_t RemoveTest<Map, K, E>::getSize() {
    return keys_.size();
}
