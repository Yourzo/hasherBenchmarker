#pragma once

#include <iostream>
#include "general_purpose_hashers.hpp"

template<size_t A> //log of alignmet when shifting
struct alignas(A) Dummy {};

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

template<typename T> struct simple_xor_shift
{
    std::size_t operator()(const T* p) const {
        auto x = reinterpret_cast<std::size_t>(p);
        x ^= x >> 11;
        x ^= x << 7;
        x ^= x >> 12;
        return x;
    }
};

template<typename T>
struct murmur2_ptr {
    const Murmur2Hash64A multipurpose_ = Murmur2Hash64A();
    std::size_t operator()(const T* p) const {
        return multipurpose_(&p, sizeof(p), 12345678);
    }
};

template<typename T>
struct murmur3_ptr {
    const Murmur3Hash64 multipurpose_ = Murmur3Hash64();
    std::size_t operator()(const T* p) const {
        return multipurpose_(&p, sizeof(p), 12345678);
    }
};