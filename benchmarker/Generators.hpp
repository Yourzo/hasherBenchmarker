#pragma once

#include <vector>
#include <random>
#include <climits>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <any>

#include "BenchmarkFactory.hpp"
#include "../hasherLib/pointer_hasher.hpp"


struct IGenerator {
	virtual ~IGenerator() = default;
    virtual std::vector<std::any> operator()(size_t count) = 0;
};

struct PointerOrderedPlaceGenerator : public IGenerator {
    std::vector<std::any> operator()(size_t count) override {
        std::vector<std::any> result;
        result.resize(count);
        auto blocks = new Dummy[count];
        for (size_t i = 0; i < count; ++i) {
            result[i] = blocks[i];
        }
        return result;
    }
};

struct PointerRandomPlaceGenerator : public IGenerator {
    std::vector<std::any> operator()(size_t count) override {
        std::vector<std::any> result;
        result.resize(count);
        for (size_t i = 0; i < count; ++i) {
            auto val = new Dummy();
            result[i] = val;
        }
        return result;
    }
};

struct BasicIntGenerator : public IGenerator {
    std::vector<std::any> operator()(size_t count) override {
        std::vector<std::any> result;
        result.resize(count);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
        for (size_t i = 0; i < count; ++i)
        {
            result[i] = dist(gen);
        }
        return result;
    }
};

struct BaseStringGenerator : public IGenerator {
	size_t length_;

    explicit BaseStringGenerator(size_t len) : length_(len) {}

     std::vector<std::any> operator()(size_t count) override {
    	std::vector<std::any> result;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(48, 122);
        for (size_t i = 0; i < count; ++i) {
            std::string currWord;
            for (size_t j = 0; j < length_; ++j) {
                currWord.push_back(static_cast<char>(dist(gen)));
            }
            result.emplace_back(currWord);
        }
        return result;
    }
};

/**
* All generated string will have length 16
* on GCC 15 and less character are stored in std::string object
* any more than that will get stored in array with pointer to it
* TODO check with somebody it might be given by system 32 vs 64bit
* characters are generated with ascii values from 48 to 122
*/
struct LongStringGenerator : public BaseStringGenerator {
	LongStringGenerator() : BaseStringGenerator(16) {}
};

struct SmallStringGenerator : public BaseStringGenerator {
    SmallStringGenerator() : BaseStringGenerator(5) {}
};

class GeneratorFactory {
public:
    static std::unordered_map<std::string, std::function<IGenerator*()>> generators_;
    static void initGens();
    static IGenerator* createGenerator(const std::string& name);
};
