#pragma once
#include <cstddef>

struct hash_int {
    std::size_t operator()(const int& x) const {
        return x;
    }
};

struct hash_int2 {
    std::size_t operator()(const int& x) const {
        return x % 128;
    }
};