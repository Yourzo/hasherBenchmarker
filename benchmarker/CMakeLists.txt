add_executable(hasher-benchmarker)

target_sources(hasher-benchmarker PRIVATE main.cpp Test.hpp)
target_compile_options(hasher-benchmarker PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-O2" "-std=gnu++20")
