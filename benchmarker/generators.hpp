#pragma once

#include <vector>
#include <random>

struct IntGenerator{
    std::vector<int>* operator()(size_t count, int min, int max) {
        auto result = new std::vector<int>(count);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min, max);
        for (size_t i = 0; i < count; ++i)
        {
            (*result)[i] = dist(gen);
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
struct LongStringGenerator {
    std::vector<std::string>* operator()(size_t count) {
        auto result = new std::vector<std::string>();
        result->reserve(count);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(48, 122);
        for (size_t i = 0; i < count; ++i) {
            std::string currWord = "";
            for (size_t j = 0; j < 16; ++j) {
                currWord = static_cast<char>(dist(gen));
            }
            (*result)[i] = currWord;
        }
        return result;
    }
};

//TODO repair, exstract repating code
struct SmallStringGEnerator {
    std::vector<std::string>* operator()(size_t count) {
        auto result = new std::vector<std::string>();
        result->reserve(count);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(48, 122);
        for (size_t i = 0; i < count; ++i) {
            std::string currWord = "";
            for (size_t j = 0; j < 5; ++j) {
                currWord = static_cast<char>(dist(gen));
            }
            (*result)[i] = currWord;
        }
        return result;
    }
};
