#pragma once

#include <vector>
#include <random>
#include <climits>
#include <unordered_map>
#include <functional>
#include <stdexcept>


struct IGenerator {
	virtual ~IGenerator() = default;
    virtual void* operator()(size_t count) = 0;
};

struct BasicIntGenerator : public IGenerator {
    void* operator()(size_t count) {
        auto result = new std::vector<int>(count);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
        for (size_t i = 0; i < count; ++i)
        {
            (*result)[i] = dist(gen);
        }
        return result;
    }
};

struct BaseStringGenerator : public IGenerator {
	size_t length_;

    explicit BaseStringGenerator(size_t len) : length_(len) {}

    void* operator()(size_t count) {
    	auto result = new std::vector<std::string>();
        result->reserve(count);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(48, 122);
        for (size_t i = 0; i < count; ++i) {
            std::string currWord = "";
            for (size_t j = 0; j < length_; ++j) {
                currWord = static_cast<char>(dist(gen));
            }
            (*result)[i] = currWord;
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
