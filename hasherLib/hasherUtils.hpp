#pragma once

#include<any>

struct BaseHasher {
    virtual ~BaseHasher() = default;
    virtual std::size_t operator()(const std::any& v) const = 0;
    virtual bool equals(const std::any& a, const std::any& b) const = 0;
};

struct HasherWrapper{
    BaseHasher& hasher_;
    explicit HasherWrapper(BaseHasher& h): hasher_(h) {}
    std::size_t operator()(const std::any& v) const {
        return hasher_(v);
    }

    bool operator()(const std::any& a, const std::any& b) const {
        return hasher_.equals(a,b);
    }
};
