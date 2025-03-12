#pragma once

#include <climits>
#include <functional>
#include <random>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "../hasherLib/pointer_hasher.hpp"
#include "BenchmarkFactory.hpp"

struct IntGenerator {
        virtual ~IntGenerator() = default;
        virtual std::vector<int> operator()(size_t count) = 0;
};

struct PointerGeneratorWrapper {};

template<typename T>
struct PointerGenerator : public PointerGeneratorWrapper {
        virtual ~PointerGenerator() = default;
        virtual std::vector<T*> operator()(size_t count) = 0;
};

// todo check if there is array to vec method
template<typename T>
struct PackedPointerGenerator : public PointerGenerator<T> {
        std::vector<T*> operator()(const size_t count) override {
            std::vector<T*> result;
            result.resize(count);
            auto blocks = new T[count];
            for (size_t i = 0; i < count; ++i) {
                result[i] = &blocks[i];
            }
            return result;
        }
};

template<typename T>
struct PointerRandomPlaceGenerator : public PointerGenerator<T> {
        std::vector<T*> operator()(size_t count) override {
            std::vector<T*> result;
            result.resize(count);
            for (size_t i = 0; i < count; ++i) {
                auto val = new T();
                result[i] = val;
            }
            return result;
        }
};

template<size_t mean, size_t stddev>
struct NormalDistributionIntGenerator : public IntGenerator {
        std::vector<int> operator()(size_t count) override {
            std::vector<int> result;
            result.resize(count);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<float> dist(mean, stddev);
            for (size_t i = 0; i < count; ++i) {
                result.push_back(dist(gen));
            }
            return result;
        }
};

struct BasicIntGenerator : public IntGenerator {
        std::vector<int> operator()(size_t count) override {
            std::vector<int> result;
            result.resize(count);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
            for (size_t i = 0; i < count; ++i) {
                result[i] = dist(gen);
            }
            return result;
        }
};

struct StringGenerator {
        virtual ~StringGenerator() = default;
        virtual std::vector<std::string> operator()(size_t count) = 0;
};

/**
 * @tparam maxLength maximum length of word
 */
template<size_t maxLength>
struct RandomStringGenerator : public StringGenerator {
        std::vector<std::string> operator()(size_t count) override {
            std::vector<std::string> result;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> charsDist(48, 122);
            std::uniform_int_distribution<size_t> length(1, maxLength);
            for (size_t i = 0; i < count; ++i) {
                std::string currWord;
                const size_t wordLen = length(gen);
                for (size_t j = 0; j < wordLen; ++j) {
                    currWord.push_back(static_cast<char>(charsDist(gen)));
                }
            }
            return result;
        }
};

/**
 * @tparam length length of generated string
 * characters are generated with ascii values from 48 to 122
 */
template<size_t length>
struct FixedLengthStringGenerator : public StringGenerator {
        std::vector<std::string> operator()(size_t count) override {
            std::vector<std::string> result;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(48, 122);
            for (size_t i = 0; i < count; ++i) {
                std::string currWord;
                for (size_t j = 0; j < length; ++j) {
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
 */
struct LongStringGenerator : public FixedLengthStringGenerator<16> {};

struct SmallStringGenerator : public FixedLengthStringGenerator<14> {};

class GeneratorFactory {
    public:
        static std::unordered_map<std::string, std::function<IntGenerator*()>>
                intGenerators_;
        static std::unordered_map<std::string,
                                  std::function<PointerGeneratorWrapper*()>>
                pointerGenerators_;
        static std::unordered_map<std::string,
                                  std::function<StringGenerator*()>>
                stringGenerators_;
        static void initGens();

        template<typename T>
        void initGens();
        static IntGenerator* createGenerator(const std::string& name);
        static StringGenerator* createStringGenerator(const std::string& name);
        static PointerGeneratorWrapper*
        createPointerGenerator(const std::string& name);
};
