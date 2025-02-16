cmake_minimum_required(VERSION 3.11)
project(HasherBenchmarker VERSION 1.0

    DESCRIPTION "Bachelors"
    LANGUAGES CXX
)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(benchmarker)
