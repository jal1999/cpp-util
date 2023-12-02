cmake_minimum_required(VERSION 3.26)
project(util)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(Boost REQUIRED)

#include_directories(${Boost_INCLUDE_DIRS})

#link_directories(${Boost_LIBRARY_DIRS})

add_executable(util main.cpp
        include/util.h
        include/custom_concepts.h)

#target_link_libraries(util ${Boost_ACCUMULATORS_LIBRARY})