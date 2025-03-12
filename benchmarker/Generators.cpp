#include "Generators.hpp"

std::unordered_map<std::string, std::function<IntGenerator*()>>
        GeneratorFactory::intGenerators_;
std::unordered_map<std::string, std::function<PointerGeneratorWrapper*()>>
        GeneratorFactory::pointerGenerators_;
std::unordered_map<std::string, std::function<StringGenerator*()>>
        GeneratorFactory::stringGenerators_;

void GeneratorFactory::initGens() {
    intGenerators_["basic int"] = []() { return new BasicIntGenerator(); };
    intGenerators_["normal dist int"] = []() {
        return new NormalDistributionIntGenerator<0, 250'000>();
    };

    stringGenerators_["long string"] = []() {
        return new LongStringGenerator();
    };
    stringGenerators_["small string"] = []() {
        return new SmallStringGenerator();
    };
    stringGenerators_["random length string"] = []() {
        return new RandomStringGenerator<30>();
    };

    pointerGenerators_["packed pointer"] = []() {
        return new PackedPointerGenerator<Dummy<32>>();
    };
    pointerGenerators_["packed pointer"] = []() {
        return new PackedPointerGenerator<Dummy<16>>();
    };
    pointerGenerators_["packed pointer"] = []() {
        return new PackedPointerGenerator<Dummy<8>>();
    };
    pointerGenerators_["packed pointer"] = []() {
        return new PackedPointerGenerator<Dummy<4>>();
    };

    pointerGenerators_["random pointer"] = []() {
        return new PointerRandomPlaceGenerator<Dummy<16>>();
    };
    pointerGenerators_["random pointer"] = []() {
        return new PointerRandomPlaceGenerator<Dummy<8>>();
    };
    pointerGenerators_["random pointer"] = []() {
        return new PointerRandomPlaceGenerator<Dummy<4>>();
    };
    pointerGenerators_["random pointer"] = []() {
        return new PointerRandomPlaceGenerator<Dummy<32>>();
    };
}

IntGenerator* GeneratorFactory::createGenerator(const std::string& name) {
    if (intGenerators_.contains(name)) {
        return intGenerators_[name]();
    };
    throw std::runtime_error("Unknown int generator type: " + name);
}

StringGenerator*
GeneratorFactory::createStringGenerator(const std::string& name) {
    if (stringGenerators_.contains(name)) {
        return stringGenerators_[name]();
    };
    throw std::runtime_error("Unknown string generator type: " + name);
}

PointerGeneratorWrapper*
GeneratorFactory::createPointerGenerator(const std::string& name) {
    if (pointerGenerators_.contains(name)) {
        return pointerGenerators_[name]();
    };
    throw std::runtime_error("Unknown pointer generator type: " + name);
}
