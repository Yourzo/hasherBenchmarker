#include "Generators.hpp"
#include "BenchmarkFactory.hpp"

int main()
{
    GeneratorFactory::initGens();
    BenchmarkFactory::initialize();
    std::vector<std::string> types = {"int"};
    std::vector<std::string> hasher = {"identity"};
    std::vector<std::string> gene = {"basic_int"};

    auto bm = BenchmarkFactory::createBenchmark(types, hasher, gene, 10, 10);
    auto res = bm->run();
    res->writeToFile();
}
