cmake_minimum_required(VERSION 3.10)

# set the project name
project(pimpl VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Library
add_library(pimpl INTERFACE)
target_include_directories(pimpl INTERFACE "./include")

# Test
add_executable(tests test.cpp a.cpp b.cpp)
find_package(Catch2 3 REQUIRED PATHS "D:/SourceCode/Catch2/build64_install")
target_link_libraries(tests PRIVATE pimpl Catch2::Catch2WithMain)

enable_testing() # enable testing functionality
add_test(NAME tests
    COMMAND $<TARGET_FILE:tests>)

# Install
install(FILES "./include/pimpl.h" DESTINATION include)

