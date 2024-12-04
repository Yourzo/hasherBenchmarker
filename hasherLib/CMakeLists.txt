add_library(hashers SHARED)

target_sources(hashers PRIVATE int_hashers.cpp)

target_compile_options(hashers PUBLIC  "-O2" "-std=gnu++20")

target_compile_options(hashers PRIVATE "-Wall" "-Wextra" "-Wpedantic")
