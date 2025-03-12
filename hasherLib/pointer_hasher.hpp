#pragma once

#include <iostream>

template<size_t A> //log of alignmet when shifting
struct alignas(A) Dummy {};

template<typename T>
struct zero_bit_count;

struct pointer_identity {
    template<typename T>
    std::size_t operator()(const T* p) const {
        return reinterpret_cast<std::size_t>(p);
    }
};

template<size_t shift, typename T>
struct pointer_shift_base {
    std::size_t operator()(const T* p) const {
        const auto x = reinterpret_cast<std::size_t>(p);
        return x >> shift;
    }
};
