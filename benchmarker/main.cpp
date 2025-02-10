#include <iostream>
#include <unordered_map>

#include "Benchmark.hpp"
#include "Result.hpp"
#include "Test.hpp"
#include "../hasherLib/int_hashers.hpp"
#include "../hasherLib/string_hashers.hpp"
#include "Generators.hpp"

template<typename K, typename T, typename H>
using map = std::unordered_map<K, T, H>;

int main()
{
    auto intGen = GeneratorFactory::createGenerator("basic_int");
    auto arr = static_cast<std::vector<int>*>((*intGen)(1));
    std::cout << (*arr)[0] << std::endl;
    Result res(10, "identity", "int");
    res.writeToFile();
}
