#include <unordered_map>

#include "Benchmark.hpp"
#include "Result.hpp"
#include "Test.hpp"
#include "../hasherLib/int_hashers.hpp"
#include "../hasherLib/string_hashers.hpp"

template<typename K, typename T, typename H>
using map = std::unordered_map<K, T, H>;

int main()
{

    Result res(10, "identity", "int");
    res.writeToFile();
}
