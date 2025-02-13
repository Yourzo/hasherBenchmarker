#include "Generators.hpp"
#include "BenchmarkFactory.hpp"

int main()
{
    GeneratorFactory::initGens();
    BenchmarkFactory::initialize();
    std::vector<std::string> types = {"int", "pointer", "long str", "small str"};
    std::vector<std::string> hasher = {"identity", "modulo pointer", "jenkins hash", "jenkins hash"};
    std::vector<std::string> gene = {"basic int", "random pointer", "long string", "small string"};

    auto bm = BenchmarkFactory::createBenchmark(types, hasher, gene, 50, 10000);
    auto res = bm->run();
    res->writeToFile();
}
