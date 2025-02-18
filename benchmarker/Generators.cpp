#include "Generators.hpp"

std::unordered_map<std::string, std::function<IntGenerator*()>> GeneratorFactory::intGenerators_;
std::unordered_map<std::string, std::function<PointerGenerator*()>> GeneratorFactory::pointerGenerators_;
std::unordered_map<std::string, std::function<StringGenerator*()>> GeneratorFactory::stringGenerators_;

void GeneratorFactory::initGens() {
	intGenerators_["basic int"] = []() { return new BasicIntGenerator(); };

	stringGenerators_["long string"] = []() { return new LongStringGenerator(); };
	stringGenerators_["small string"] = []() { return new SmallStringGenerator(); };

	pointerGenerators_["packed pointer"] = [](){ return new PackedPointerGenerator(); };
	pointerGenerators_["random pointer"] = [](){ return new PointerRandomPlaceGenerator(); };
}

IntGenerator* GeneratorFactory::createGenerator(const std::string& name) {
    if (intGenerators_.contains(name)) {
        	return intGenerators_[name]();
    };
	throw std::runtime_error("Unknown int generator type: " + name);
}

StringGenerator * GeneratorFactory::createStringGenerator(const std::string &name) {
	if (stringGenerators_.contains(name)) {
        	return stringGenerators_[name]();
    };
	throw std::runtime_error("Unknown string generator type: " + name);
}

PointerGenerator * GeneratorFactory::createPointerGenerator(const std::string &name) {
	if (pointerGenerators_.contains(name)) {
        	return pointerGenerators_[name]();
    };
	throw std::runtime_error("Unknown pointer generator type: " + name);
}
