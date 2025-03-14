#pragma once

#include <iostream>

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
    std::size_t operator()(const T* p) const
    {
        auto x = reinterpret_cast<std::size_t>(p);
        x ^= x >> 11;
        x ^= x << 7;
        x ^= x >> 12;
        return x;
    }
};

//TODO add reinterpret casts and fix murmur3 mb

template<typename T> struct murmur2
{
	std::size_t operator()(T const* k) const
	{
		const unsigned int m = 0x5bd1e995;

		uint32_t h = 4;

		auto d = reinterpret_cast<size_t>(k);

		d *= m;
		d ^= d >> 24;
		d *= m;

		h *= m;
		h ^= d;


		h ^= h >> 13;
		h *= m;
		h ^= h >> 15;

		return h;
	}
};

template<typename T> struct murmur3
{
    // Hardcoded input size = 4.
    // Omitted xor with input size in the final mix step, as that's a constant,
    // and this only flips a single bit (waste of CPU cycles).

    template<int r> constexpr uint32_t rotl(uint32_t x) const { return (x << r) | (x >> (32 - r)); }

    unsigned int fmix32( unsigned int h ) const
    {
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;
        return h;
    }

    std::size_t operator()(T const* k) const
    {
        constexpr unsigned int c1 = 0xcc9e2d51;
        constexpr unsigned int c2 = 0x1b873593;

        auto h = reinterpret_cast<size_t>(k);

        h *= c1;
        h = rotl<15>(h);
        h *= c2;

        h = rotl<13>(h);
        h = h*5+0xe6546b64;

        return fmix32(h);
    }
};
