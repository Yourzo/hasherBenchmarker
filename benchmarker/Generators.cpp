#include "Generators.hpp"

std::unordered_map<std::string, std::function<IGenerator*()>> GeneratorFactory::generators_;

void GeneratorFactory::initGens() {
	generators_["basic_int"] = []() { return new BasicIntGenerator(); };
	generators_["long_string"] = []() { return new LongStringGenerator(); };
	generators_["small_string"] = []() { return new SmallStringGenerator(); };
}

IGenerator* GeneratorFactory::createGenerator(const std::string& name) {
    if (generators_.contains(name)) {
        	return generators_[name]();
    };
	throw std::runtime_error("Unknown generator type: " + name);
}