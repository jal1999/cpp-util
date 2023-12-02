cmake_minimum_required(VERSION 3.26)
project(util)

set(CMAKE_CXX_STANDARD 20)

add_executable(util main.cpp
        util.h
        custom_concepts.h)
