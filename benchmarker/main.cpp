#include <fstream>
#include "BenchmarkFactory.hpp"
#include "Generators.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {

    std::ifstream jsonFile("config.json");
    if (!jsonFile) {
        std::cout << "no config.json deleted in";
        std::cout << std::filesystem::current_path() << std::endl;
        return 1;
    }
    json j;
    jsonFile >> j;
    GeneratorFactory::initGens();
    size_t replications = j.value("replications", 20);
    bool shuffle = j.value("shuffle", false);
    for (const auto& jsonPart: j["benchmarks"]) {
        std::vector<TestDescriptor> descs;
        for (const auto& benchmark: jsonPart) {
            TestDescriptor desc {
                .name_ = benchmark["name"],
                .generator_ = benchmark["generator"],
                .hasher_ = benchmark["hasher"],
                .mapSize_ = benchmark["map size"]
            };
            descs.push_back(desc);
        }
        auto bm = BenchmarkFactory::createBenchmark(descs, replications, shuffle);
        auto res = bm->run();
        res->writeToFile();
        delete bm;
        delete res;
    }
    std::cout << "Results in: "
              << std::filesystem::current_path().string() + "/results"
              << std::endl;
}
