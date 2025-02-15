#include "Generators.hpp"
#include "BenchmarkFactory.hpp"

int main()
{
    GeneratorFactory::initGens();
    BenchmarkFactory::initialize();
    std::vector<std::string> types = { "pointer - 1 000 000", "pointer - 1 000"};
    std::vector<std::string> hasher = {"shift 4 pointer", "shift 3 pointer"};
    std::vector<std::string> gene = {"random pointer", "random pointer"};
    std::vector<size_t> mapSizes = {1000000, 1000};

    auto bm = BenchmarkFactory::createBenchmark(types, hasher, gene, 15, mapSizes);
    auto res = bm->run();
    res->writeToFile();
}
