#include <fstream>

#include "Generators.hpp"
#include "BenchmarkFactory.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main()
{

    std::ifstream jsonFile("config.json");
    if (!jsonFile) {
        std::cout << "no config.json deteted in";
        std::cout << std::filesystem::current_path() << std::endl;
        return 1;
    }
    json j;
    jsonFile >> j;
    GeneratorFactory::initGens();
    BenchmarkFactory::initialize();
    size_t replications = j.value("replications", 20);
    for (const auto& jsonPart: j["benchmarks"]) {
        std::vector<std::string> types;
        std::vector<std::string> hasher;
        std::vector<std::string> gene;
        std::vector<size_t> mapSizes;
        for (const auto& benchmark: jsonPart) {
            types.push_back(benchmark["name"]);
            hasher.push_back(benchmark["hasher"]);
            gene.push_back(benchmark["generator"]);
            mapSizes.push_back(benchmark["map size"]);
        }
        auto bm = BenchmarkFactory::createBenchmark(types, hasher, gene, replications, mapSizes);
        auto res = bm->run();
        res->writeToFile();
    }
}
