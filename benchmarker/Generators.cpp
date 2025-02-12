#include "Generators.hpp"

std::unordered_map<std::string, std::function<IGenerator*()>> GeneratorFactory::generators_;

void GeneratorFactory::initGens() {
	generators_["basic int"] = []() { return new BasicIntGenerator(); };
	generators_["long string"] = []() { return new LongStringGenerator(); };
	generators_["small string"] = []() { return new SmallStringGenerator(); };
	generators_["packed pointer"] = [](){ return new PointerOrderedPlaceGenerator(); };
	generators_["random pointer"] = [](){ return new PointerRandomPlaceGenerator(); };
}

IGenerator* GeneratorFactory::createGenerator(const std::string& name) {
    if (generators_.contains(name)) {
        	return generators_[name]();
    };
	throw std::runtime_error("Unknown generator type: " + name);
}
