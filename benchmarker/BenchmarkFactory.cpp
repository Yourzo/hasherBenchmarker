#include "BenchmarkFactory.hpp"

#include "../hasherLib/int_hashers.hpp"
#include "../hasherLib/pointer_hasher.hpp"
#include "../hasherLib/string_hashers.hpp"
#include "Generators.hpp"
#include "Test.hpp"

Benchmark* BenchmarkFactory::createBenchmark(
        const std::vector<std::string>& types,
        const std::vector<std::string>& hashers,
        const std::vector<std::string>& generators, const size_t replications,
        const std::vector<size_t>& mapSizes, const bool shuffle) {
    auto* result = new Benchmark("test", mapSizes, replications, shuffle);
    for (size_t i = 0; i < types.size(); ++i) {
        load(i + 1, types.size());
        TestDescriptor data{.name_ = types[i],
                            .generator_ = generators[i],
                            .hasher_ = hashers[i],
                            .mapSize_ = mapSizes[i]};
        result->addTest(createTest(data));
    }
    return result;
}

TestBase* BenchmarkFactory::createTest(const TestDescriptor& descriptor) {
    if (descriptor.hasher_ == "identity") {
        return new Test<std::unordered_map<int, int, identity_int>, int,
                        IntGenerator*>(
                GeneratorFactory::createGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "std::hash int") {
        return new Test<std::unordered_map<int, int>, int, IntGenerator*>(
                GeneratorFactory::createGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "jenkins 32 bit") {
        return new Test<std::unordered_map<int, int, jenkins_32bit>, int,
                        IntGenerator*>(
                GeneratorFactory::createGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "hash 1") {
        return new Test<std::unordered_map<int, int, hash1>, int,
                        IntGenerator*>(
                GeneratorFactory::createGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "multiplication hash") {
        return new Test<std::unordered_map<int, int, multiplication_hash>, int,
                        IntGenerator*>(
                GeneratorFactory::createGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "murmur2_int") {
        return new Test<std::unordered_map<int, int, murmur2_int>, int,
                        IntGenerator*>(
                GeneratorFactory::createGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "murmur3_int") {
        return new Test<std::unordered_map<int, int, murmur3_int>, int,
                        IntGenerator*>(
                GeneratorFactory::createGenerator(descriptor.generator_),
                descriptor);
    }

    if (descriptor.hasher_ == "rolling hash") {
        return new Test<std::unordered_map<std::string, int, rolling_sum_hash>,
                        std::string, StringGenerator*>(
                GeneratorFactory::createStringGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "jenkins hash") {
        return new Test<std::unordered_map<std::string, int, jenkins_hash>,
                        std::string, StringGenerator*>(
                GeneratorFactory::createStringGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "std::hash string") {
        return new Test<std::unordered_map<std::string, int>, std::string,
                        StringGenerator*>(
                GeneratorFactory::createStringGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "djb2") {
        return new Test<std::unordered_map<std::string, int>, std::string,
                        StringGenerator*>(
                GeneratorFactory::createStringGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "sdbm") {
        return new Test<std::unordered_map<std::string, int>, std::string,
                        StringGenerator*>(
                GeneratorFactory::createStringGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "murmur2_str") {
        return new Test<std::unordered_map<std::string, int, murmur2_string>, std::string,
                        StringGenerator*>(
                GeneratorFactory::createStringGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "murmur3_str") {
        return new Test<std::unordered_map<std::string, int, murmur3_string>, std::string,
                        StringGenerator*>(
                GeneratorFactory::createStringGenerator(descriptor.generator_),
                descriptor);
    }

    if (descriptor.hasher_ == "shift 4 pointer align 16") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<16>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<16>*, int,
                                           pointer_shift_base<4, Dummy<16>>>,
                        Dummy<16>*, PointerGenerator<Dummy<16>>*>(generator,
                                                                  descriptor);
    } else if (descriptor.hasher_ == "shift 3 pointer align 8") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<8>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<8>*, int,
                                           pointer_shift_base<3, Dummy<8>>>,
                        Dummy<8>*, PointerGenerator<Dummy<8>>*>(generator,
                                                                descriptor);
    } else if (descriptor.hasher_ == "shift 5 pointer align 32") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<32>>*>(
                GeneratorFactory::createGenerator(descriptor.generator_));

        return new Test<std::unordered_map<Dummy<32>*, int,
                                           pointer_shift_base<5, Dummy<32>>>,
                        Dummy<32>*, PointerGenerator<Dummy<32>>*>(generator,
                                                                  descriptor);
    } else if (descriptor.hasher_ == "std::hash ptr") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<4>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<4>*, int>, Dummy<4>*,
                        PointerGenerator<Dummy<4>>*>(generator, descriptor);
    } else if (descriptor.hasher_ == "murmur2_ptr") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<4>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<4>*, int, murmur2_ptr<Dummy<4>>>,
                        Dummy<4>*, PointerGenerator<Dummy<4>>*>(generator,
                                                                descriptor);
    } else if (descriptor.hasher_ == "murmur3_ptr") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<4>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));
        return new Test<std::unordered_map<Dummy<4>*, int, murmur3_ptr<Dummy<4>>>,
                        Dummy<4>*, PointerGenerator<Dummy<4>>*>(generator,
                                                                descriptor);
    }
    throw std::invalid_argument("Hasher: <" + descriptor.hasher_ +
                                "> not recognized");
}

void BenchmarkFactory::load(const size_t done, const size_t count) {
    std::cout << "Building benchmark: " << done << "/" << count << "\r";
    std::cout.flush();
    if (done == count)
        std::cout << std::endl;
}
