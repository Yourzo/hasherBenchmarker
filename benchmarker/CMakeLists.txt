add_executable(hasher-benchmarker)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
target_link_libraries(hasher-benchmarker PRIVATE nlohmann_json::nlohmann_json)
target_sources(hasher-benchmarker PRIVATE main.cpp Test.hpp Benchmark.cpp Result.cpp Generators.cpp BenchmarkFactory.cpp)
target_compile_options(hasher-benchmarker PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")