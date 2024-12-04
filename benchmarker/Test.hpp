#pragma once

#include <vector>

template<typename Map, typename K, typename E>
class Test
{
protected:
    Map* map_;
public:
    explicit Test(Map *map);
    size_t getMapSize();
    virtual void after() = 0;
    virtual void execute() = 0;
    virtual void before() = 0;
    virtual ~Test();
};

template<typename Map, typename K, typename E>
class LookupTest : public Test<Map, K, E>
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
    ~LookupTest() override;
};

template<typename Map, typename K, typename E>
class InsertTest : public Test<Map, K, E>
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
    ~InsertTest() override;
};

template<typename Map, typename K, typename E>
class RemoveTest : public Test<Map, K, E>
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
    ~RemoveTest() override;
};

template<typename Map, typename K, typename E>
Test<Map, K, E>::Test(Map *map)
{
    map_ = map;
}

template<typename Map, typename K, typename E>
Test<Map, K, E>::~Test()
{
    delete map_;
}

template<typename Map, typename K, typename E>
size_t Test<Map, K, E>::getMapSize()
{
    return map_->size();
}

template<typename Map, typename K, typename E>
LookupTest<Map, K, E>::LookupTest(Map* map, std::vector<K> &&keys):
Test<Map, K, E>(map), keys_(keys) {}


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
LookupTest<Map, K, E>::~LookupTest() {
}

template<typename Map, typename K, typename E>
InsertTest<Map, K, E>::InsertTest(Map *map, std::vector<K> &&keys, E dummyVal):
Test<Map, K, E>(map), dummyVal_(dummyVal), keys_(keys) {}

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
InsertTest<Map, K, E>::~InsertTest() {
}

template<typename Map, typename K, typename E>
RemoveTest<Map, K, E>::RemoveTest(Map *map, std::vector<K> &&keys): Test<Map, K, E>(map), keys_(keys) {
}

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
RemoveTest<Map, K, E>::~RemoveTest() {
}
