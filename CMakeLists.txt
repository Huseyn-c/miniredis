cmake_minimum_required(VERSION 3.20)
project(miniredis CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

add_library(miniredis_core
    src/storage.cpp
    src/commands.cpp
    src/command_registry.cpp
    src/parser.cpp
)
target_include_directories(miniredis_core PUBLIC src)

add_executable(miniredis src/main.cpp)
target_link_libraries(miniredis PRIVATE miniredis_core)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(tests tests/storage_test.cpp tests/commands_test.cpp)
target_link_libraries(tests PRIVATE miniredis_core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)