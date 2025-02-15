#include "Generators.hpp"
#include "BenchmarkFactory.hpp"

int main()
{
    GeneratorFactory::initGens();
    BenchmarkFactory::initialize();
    std::vector<std::string> types = { "pointer3", "pointer1"};
    std::vector<std::string> hasher = {"shift 4 pointer", "shift 3 pointer"};
    std::vector<std::string> gene = {"random pointer", "random pointer"};

    auto bm = BenchmarkFactory::createBenchmark(types, hasher, gene, 10000, 100000);
    auto res = bm->run();
    res->writeToFile();
}
