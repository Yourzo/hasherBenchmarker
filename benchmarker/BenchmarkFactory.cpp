#include "BenchmarkFactory.hpp"

#include "../hasherLib/int_hashers.hpp"
#include "../hasherLib/pointer_hasher.hpp"
#include "../hasherLib/string_hashers.hpp"
#include "Generators.hpp"
#include "Test.hpp"

Benchmark* BenchmarkFactory::createBenchmark(
        const std::vector<TestDescriptor>& descs, size_t replications,
        bool shuffle) {
    auto* result = new Benchmark("test", descs.size(), replications, shuffle);
    for (size_t i = 0; i < descs.size(); ++i) {
        load(i + 1, descs.size());
        result->addTest(createTest(descs[i]));
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
        return new Test<std::unordered_map<std::string, int, djb2>, std::string,
                        StringGenerator*>(
                GeneratorFactory::createStringGenerator(descriptor.generator_),
                descriptor);
    } else if (descriptor.hasher_ == "sdbm") {
        return new Test<std::unordered_map<std::string, int, sdbm>, std::string,
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
                GeneratorFactory::createPointerGenerator(descriptor.generator_));

        return new Test<std::unordered_map<Dummy<32>*, int,
                                           pointer_shift_base<5, Dummy<32>>>,
                        Dummy<32>*, PointerGenerator<Dummy<32>>*>(generator,
                                                                  descriptor);
    } else if (descriptor.hasher_ == "std::hash ptr") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<8>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<8>*, int>, Dummy<8>*,
                        PointerGenerator<Dummy<8>>*>(generator, descriptor);
    } else if (descriptor.hasher_ == "simple xor shift") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<8>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<8>*, int, simple_xor_shift<Dummy<8>>>,
                        Dummy<8>*, PointerGenerator<Dummy<8>>*>(generator,
                                                                descriptor);
    } else if (descriptor.hasher_ == "murmur2_ptr") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<8>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<8>*, int, murmur2_ptr<Dummy<8>>>,
                        Dummy<8>*, PointerGenerator<Dummy<8>>*>(generator,
                                                                descriptor);
    } else if (descriptor.hasher_ == "murmur3_ptr") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<8>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));
        return new Test<std::unordered_map<Dummy<8>*, int, murmur3_ptr<Dummy<8>>>,
                        Dummy<8>*, PointerGenerator<Dummy<8>>*>(generator,
                                                                descriptor);
    } else if (descriptor.hasher_ == "std::hash ptr align 16") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<16>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<16>*, int>, Dummy<16>*,
                        PointerGenerator<Dummy<16>>*>(generator, descriptor);
    } else if (descriptor.hasher_ == "simple xor shift align 16") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<16>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<16>*, int, simple_xor_shift<Dummy<16>>>,
                        Dummy<16>*, PointerGenerator<Dummy<16>>*>(generator,
                                                                descriptor);
    } else if (descriptor.hasher_ == "murmur2_ptr align 16") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<16>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<16>*, int, murmur2_ptr<Dummy<16>>>,
                        Dummy<16>*, PointerGenerator<Dummy<16>>*>(generator,
                                                                descriptor);
    } else if (descriptor.hasher_ == "murmur3_ptr align 16") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<16>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));
        return new Test<std::unordered_map<Dummy<16>*, int, murmur3_ptr<Dummy<16>>>,
                        Dummy<16>*, PointerGenerator<Dummy<16>>*>(generator,
                                                                descriptor);
    } else if (descriptor.hasher_ == "std::hash ptr align 32") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<32>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<32>*, int>, Dummy<32>*,
                        PointerGenerator<Dummy<32>>*>(generator, descriptor);
    } else if (descriptor.hasher_ == "simple xor shift align 32") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<32>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<32>*, int, simple_xor_shift<Dummy<32>>>,
                        Dummy<32>*, PointerGenerator<Dummy<32>>*>(generator,
                                                                descriptor);
    } else if (descriptor.hasher_ == "murmur2_ptr align 32") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<32>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));

        return new Test<std::unordered_map<Dummy<32>*, int, murmur2_ptr<Dummy<32>>>,
                        Dummy<32>*, PointerGenerator<Dummy<32>>*>(generator,
                                                                descriptor);
    } else if (descriptor.hasher_ == "murmur3_ptr align 32") {
        auto generator = reinterpret_cast<PointerGenerator<Dummy<32>>*>(
                GeneratorFactory::createPointerGenerator(
                        descriptor.generator_));
        return new Test<std::unordered_map<Dummy<32>*, int, murmur3_ptr<Dummy<32>>>,
                        Dummy<32>*, PointerGenerator<Dummy<32>>*>(generator,
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
