#pragma once

#include <cstddef>
#include <any>

#include "hasherUtils.hpp"

struct hash_int : public BaseHasher {
    std::size_t operator()(const std::any& v) const {
        if (v.type() != typeid(int)) {
            throw std::bad_any_cast();
        }
        const auto x = std::any_cast<int>(v);
        return x;
    }

    bool equals(const std::any& a, const std::any& b) const {
        return std::any_cast<int>(a) == std::any_cast<int>(b);
    }
};

struct hash_int2 : public BaseHasher {
    std::size_t operator()(const std::any& v) const {
        if (v.type() != typeid(int)) {
            throw std::bad_any_cast();
        }
        const auto x = std::any_cast<int>(v);
        return x % 128;
    }

    bool equals(const std::any& a, const std::any& b) const {
        return std::any_cast<int>(a) == std::any_cast<int>(b);
    }
};