#include "BenchmarkFactory.hpp"

#include "../hasherLib/int_hashers.hpp"
#include "../hasherLib/string_hashers.hpp"
#include "../hasherLib/pointer_hasher.hpp"
#include "Generators.hpp"
#include "Test.hpp"

std::unordered_map<std::string, BaseHasher*> BenchmarkFactory::hashers_;

Benchmark* BenchmarkFactory::createBenchmark(const std::vector<std::string> &types, const std::vector<std::string> &hashers, const std::vector<std::string> &generators,
                                    const size_t replications, const size_t mapSize) {
    auto* result = new Benchmark("test", mapSize, replications);
    for (size_t i = 0; i < types.size(); ++i) {
        result->addTest(createTest(types[i], hashers[i],mapSize, generators[i]));
    }
    return result;
}

/**
 * Register your custom hasher here:
 */
void BenchmarkFactory::initialize() {
    hashers_["identity"] = new hash_int();
    hashers_["modulo"] = new hash_int2();
    hashers_["rolling hash"] = new rolling_sum_hash();
    hashers_["jenkins hash"] = new jenkins_hash();
    hashers_["modulo pointer"] = new pointer_modulo();
    hashers_["shift 4 pointer"] = new pointer_shift();
}

TestBase* BenchmarkFactory::createTest(const std::string &type, const std::string &hasher, const size_t size, const std::string& generator) {
    BaseHasher& chosenHasher = *hashers_[hasher];
    HasherWrapper hasherWrapper(chosenHasher);
    auto hashMap = new std::unordered_map<std::any, int, HasherWrapper, HasherWrapper>(size, hasherWrapper, hasherWrapper);

    IGenerator* gen = GeneratorFactory::createGenerator(generator);
    auto keys = (*gen)(size);

    for (size_t i = 0; i < size; ++i) {
        (*hashMap)[keys[i]] = 0;
    }
    return new Test<decltype(hashMap), std::any, int>(
        hashMap, "test", std::move(keys), hasher, type
    );
}