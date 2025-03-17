#pragma once

#include <cstddef>
#include <string>


//most of these are string hashers: https://burtleburtle.net/bob/hash/doobs.html

struct rolling_sum_hash {
    std::size_t operator()(const std::string& s) const {
        unsigned int a = 63689;
        unsigned int hash = 0;
        for (size_t i = 0; i < s.length(); i++) {
            constexpr unsigned int b = 378551;
            hash = hash * a + s[i];
            a = a * b;
        }
        return hash & 0x7FFFFFFF;
    }
};

struct jenkins_hash { //polynomial rolling hash
    std::size_t operator()(const std::string& s) const {
        unsigned int hash = 1315423911;
        for (size_t i = 0; i < s.length(); i++) {
            hash ^= (hash << 5) + s[i] + (hash >> 2);
        }
        return hash & 0x7FFFFFFF;
    }
};

struct djb2 {
    std::size_t operator()(const std::string& s) const {
        std::size_t hash = 5318;
        for (const char c : s) {
            hash = (hash << 5) + hash + c;
        }
        return hash;
    }
};

struct sdbm {
    std::size_t operator()(const std::string& s) const {
        std::size_t hash = 0;
        for (const char c : s) {
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
        return hash;
    }
};
