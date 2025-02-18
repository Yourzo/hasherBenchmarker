#pragma once

#include <iostream>

struct Dummy {
    char dummyData_[4];
};

template<size_t shift>
struct pointer_shift_base {
    std::size_t operator()(const Dummy* p) const {
        const auto x = reinterpret_cast<std::size_t>(p);
        return x >> shift;
    }
};

/**
* General purpose, for data in vector next to each other I need to create something else
* modulo 256
*/
struct pointer_modulo_256 {
    std::size_t operator()(const Dummy* p) const {
        const auto x = reinterpret_cast<std::size_t>(p);
        return x % 256;
    }
};

