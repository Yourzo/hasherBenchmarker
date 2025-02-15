#pragma once

#include "hasherUtils.hpp"
#include <iostream>

struct Dummy {
    char dummyData_[4];
};

struct pointer_shift_base : public BaseHasher {
    size_t shiftVal_;
    explicit pointer_shift_base(size_t val) : shiftVal_(val) {};
    std::size_t operator()(const std::any& v) const override {
        if (v.type() != typeid(Dummy*)) {
            throw std::bad_any_cast();
        }
        const auto x = std::any_cast<Dummy*>(v);
        const auto y = reinterpret_cast<std::size_t>(x);
        return y >> shiftVal_;
    }

    bool equals(const std::any& a, const std::any& b) const override {
        return std::any_cast<Dummy*>(a) == std::any_cast<Dummy*>(b);
    }
};

/**
* General purpose, for data in vector next to each other I need to create something else
* modulo 256
*/
struct pointer_modulo_256 : public BaseHasher {
    std::size_t operator()(const std::any& v) const override {
        if (v.type() != typeid(Dummy*)) {
            throw std::bad_any_cast();
        }
        const auto x = std::any_cast<Dummy*>(v);
        const auto y = reinterpret_cast<std::size_t>(x);
        return y % 256;
    }

    bool equals(const std::any& a, const std::any& b) const override {
        return std::any_cast<Dummy*>(a) == std::any_cast<Dummy*>(b);
    }
};

/**
* this might be useful when objects are packed tightly, not just random in
*/
struct pointer_shift_4 : public pointer_shift_base {
    pointer_shift_4() : pointer_shift_base(4) {}
};

struct pointer_shift_3 : public pointer_shift_base {
    pointer_shift_3() :pointer_shift_base(3) {}
};
