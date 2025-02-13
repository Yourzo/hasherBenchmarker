#pragma once

#include "hasherUtils.hpp"
#include <iostream>

struct Dummy {
    char dummyData_[4];
};

/**
* General purpose, for data in vector next to each other I need to create something else
*/
struct pointer_modulo : public BaseHasher {
    std::size_t operator()(const std::any& v) const {
        if (v.type() != typeid(Dummy*)) {
            std::cout << "PROblem???" << std::endl;
            throw std::bad_any_cast();
        }
        const auto x = std::any_cast<Dummy*>(v);
        const auto y = reinterpret_cast<std::size_t>(x);
        return y % 256;
    }

    bool equals(const std::any& a, const std::any& b) const {
        return std::any_cast<Dummy*>(a) == std::any_cast<Dummy*>(b);
    }
};

/**
* this might be usefull when objects are packed tigthly, not just random in
*/
struct pointer_shift : public BaseHasher {
    std::size_t operator()(const std::any& v) const {
        if (v.type() != typeid(Dummy*)) {
            throw std::bad_any_cast();
        }
        const auto x = std::any_cast<Dummy*>(v);
        const auto y = reinterpret_cast<std::size_t>(x);
        return y >> 4;
    }

    bool equals(const std::any& a, const std::any& b) const {
        return std::any_cast<Dummy*>(a) == std::any_cast<Dummy*>(b);
    }
};