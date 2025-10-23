cmake_minimum_required(VERSION 3.14)
project(DualNumbersProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DualNumbersLib
    src/DualNumbers.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(DualNumbersTests
    tests/DualNumbersTests.cpp
)
target_link_libraries(DualNumbersTests PRIVATE DualNumbersLib GTest::gtest_main pthread)

enable_testing()
include(GoogleTest)
gtest_discover_tests(DualNumbersTests)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../tests)
install(TARGETS DualNumbersTests DESTINATION tests)
set_target_properties(DualNumbersTests PROPERTIES OUTPUT_NAME CTest)
