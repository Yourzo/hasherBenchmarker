#pragma once

//https://github.com/aappleby/smhasher/blob/0ff96f7835817a27d0487325b6c16033e2992eb5/src/MurmurHash2.cpp#L96

struct Murmur2Hash64A {
    std::size_t operator()( const void * key, int len, std::size_t seed ) const {
        constexpr std::size_t m = 0xc6a4a7935bd1e995LLU;
        constexpr int r = 47;

        std::size_t h = seed ^ (len * m);

        auto data = static_cast<const uint8_t *>(key);
        const uint8_t * end = data + (len/8);

        while(data != end)
        {
            std::size_t k = *data++;

            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;
        }

        const unsigned char * data2 = (const unsigned char*)data;

        switch(len & 7)
        {
            case 7: h ^= std::size_t(data2[6]) << 48;
            case 6: h ^= std::size_t(data2[5]) << 40;
            case 5: h ^= std::size_t(data2[4]) << 32;
            case 4: h ^= std::size_t(data2[3]) << 24;
            case 3: h ^= std::size_t(data2[2]) << 16;
            case 2: h ^= std::size_t(data2[1]) << 8;
            case 1: h ^= std::size_t(data2[0]);
            h *= m;
        };

        h ^= h >> r;
        h *= m;
        h ^= h >> r;

        return h;
    }
};

//https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp

inline uint32_t rotl32 ( uint32_t x, int8_t r )
{
    return (x << r) | (x >> (32 - r));
}

inline uint64_t rotl64 ( uint64_t x, int8_t r )
{
    return (x << r) | (x >> (64 - r));
}

#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y)	rotl64(x,y)

#define BIG_CONSTANT(x) (x##LLU)

#define	FORCE_INLINE inline __attribute__((always_inline))

FORCE_INLINE uint64_t getblock64 ( const uint64_t * p, int i )
{
    return p[i];
}

FORCE_INLINE uint64_t fmix64 ( uint64_t k )
{
    k ^= k >> 33;
    k *= BIG_CONSTANT(0xff51afd7ed558ccd);
    k ^= k >> 33;
    k *= BIG_CONSTANT(0xc4ceb9fe1a85ec53);
    k ^= k >> 33;

    return k;
}

struct Murmur3Hash64 {
    std::size_t operator()( const void * key, const int len, const uint32_t seed) const
    {
        const uint8_t * data = (const uint8_t*)key;
        const int nblocks = len / 16;

        std::size_t h1 = seed;
        std::size_t h2 = seed;

        const std::size_t c1 = BIG_CONSTANT(0x87c37b91114253d5);
        const std::size_t c2 = BIG_CONSTANT(0x4cf5ad432745937f);

        //----------
        // body

        const std::size_t * blocks = (const std::size_t *)(data);

        for(int i = 0; i < nblocks; i++)
        {
            std::size_t k1 = getblock64(blocks,i*2+0);
            std::size_t k2 = getblock64(blocks,i*2+1);

            k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;

            h1 = ROTL64(h1,27); h1 += h2; h1 = h1*5+0x52dce729;

            k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;

            h2 = ROTL64(h2,31); h2 += h1; h2 = h2*5+0x38495ab5;
        }

        //----------
        // tail

        const uint8_t * tail = (const uint8_t*)(data + nblocks*16);

        std::size_t k1 = 0;
        std::size_t k2 = 0;

        switch(len & 15)
        {
            case 15: k2 ^= ((std::size_t)tail[14]) << 48;
            case 14: k2 ^= ((std::size_t)tail[13]) << 40;
            case 13: k2 ^= ((std::size_t)tail[12]) << 32;
            case 12: k2 ^= ((std::size_t)tail[11]) << 24;
            case 11: k2 ^= ((std::size_t)tail[10]) << 16;
            case 10: k2 ^= ((std::size_t)tail[ 9]) << 8;
            case  9: k2 ^= ((std::size_t)tail[ 8]) << 0;
            k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;

            case  8: k1 ^= ((std::size_t)tail[ 7]) << 56;
            case  7: k1 ^= ((std::size_t)tail[ 6]) << 48;
            case  6: k1 ^= ((std::size_t)tail[ 5]) << 40;
            case  5: k1 ^= ((std::size_t)tail[ 4]) << 32;
            case  4: k1 ^= ((std::size_t)tail[ 3]) << 24;
            case  3: k1 ^= ((std::size_t)tail[ 2]) << 16;
            case  2: k1 ^= ((std::size_t)tail[ 1]) << 8;
            case  1: k1 ^= ((std::size_t)tail[ 0]) << 0;
            k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;
        };

        //----------
        // finalization

        h1 ^= len; h2 ^= len;

        h1 += h2;
        h2 += h1;

        h1 = fmix64(h1);
        h2 = fmix64(h2);

        h1 += h2;
        h2 += h1;

        return h2;
    }
};
