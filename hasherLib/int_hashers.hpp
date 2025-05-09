#pragma once

#include <cstddef>
#include <iostream>
#include <limits>

#include "general_purpose_hashers.hpp"

struct fill_hash {
    std::size_t operator()(const int& x) const {
        std::size_t res = x;
        if (x < 0) {
            res += std::numeric_limits<int>::max();
        }
        return res;
    }
};

//https://burtleburtle.net/bob/hash/doobs.html this might be a great source for me

/**
 * https://burtleburtle.net/bob/hash/integer.html
 */
struct hash1 {
    std::size_t operator()(const int& x) const {
        std::size_t a = x;
        a = (a ^ 61) ^ (a >> 16);
        a = a + (a << 3);
        a = a ^ (a >> 4);
        a = a * 0x27d4eb2d;
        a = a ^ (a >> 15);
        return a;
    }
};

/**
 * https://gist.github.com/badboy/6267743#robert-jenkins-32-bit-integer-hash-function
 */
struct jenkins_32bit {
    std::size_t operator()(const int& x) const {
        std::size_t res = x;
        res = (res + 0x7ed55d16) + (res << 12);
        res = (res ^ 0xc761c23c) ^ (res >> 19);
        res = (res + 0x165667b1) + (res << 5);
        res = (res + 0xd3a2646c) ^ (res << 9);
        res = (res + 0xfd7046c5) + (res << 3);
        res = (res ^ 0xb55a4f09) ^ (res >> 16);
        return res;
    }
};

/**
 * https://gist.github.com/badboy/6267743#using-multiplication-for-hashing
 * casting might be problem
 */
struct multiplication_hash {
    std::size_t operator()(const int& x) const {
        std::size_t key = x;
        constexpr int c2 = 0x27d4eb2d; // a prime or an odd constant
        key = (key ^ 61) ^ (key >> 16);
        key = key + (key << 3);
        key = key ^ (key >> 4);
        key = key * c2;
        key = key ^ (key >> 15);
        return key;
    }
};

struct identity_int {
    std::size_t operator()(const int& x) const {
        return x;
    }
};

struct murmur2_int {
    const Murmur2Hash64A multipurpose_ = Murmur2Hash64A();
    std::size_t operator()(const int& x) const {
        return multipurpose_(&x, sizeof(x), 0x9747b28c);
    }
};

struct murmur3_int {
    const Murmur3Hash64 multipurpose_ = Murmur3Hash64();
    std::size_t operator()(const int& x) const {
        return multipurpose_(&x, sizeof(x), 12346578);
    }
};
