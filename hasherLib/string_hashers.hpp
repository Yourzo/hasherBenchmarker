#pragma once

#include <any>
#include <cstddef>
#include <string>

#include "hasherUtils.hpp"

struct rolling_sum_hash : public BaseHasher {
    std::size_t operator()(const std::any& v) const override {
        if (v.type() != typeid(std::string)) {
            throw std::bad_any_cast();
        }
        const auto s = std::any_cast<std::string>(v);
        unsigned int a = 63689;
        unsigned int hash = 0;
        for (size_t i = 0; i < s.length(); i++) {
            constexpr unsigned int b = 378551;
            hash = hash * a + s[i];
            a = a * b;
        }
        return hash & 0x7FFFFFFF;
    }

    bool equals(const std::any& a, const std::any& b) const override {
        return std::any_cast<std::string>(a) == std::any_cast<std::string>(b);
    }
};

struct jenkins_hash : public BaseHasher { //polynomial rolling hash
    std::size_t operator()(const std::any& v) const override {
        if (v.type() != typeid(std::string)) {
            throw std::bad_any_cast();
        }
        const auto s = std::any_cast<std::string>(v);
        unsigned int hash = 1315423911;
        for (size_t i = 0; i < s.length(); i++) {
            hash ^= (hash << 5) + s[i] + (hash >> 2);
        }
        return hash & 0x7FFFFFFF;
    }

    bool equals(const std::any& a, const std::any& b) const override {
        return std::any_cast<std::string>(a) == std::any_cast<std::string>(b);
    }
};
