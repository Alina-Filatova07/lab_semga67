cmake_minimum_required(VERSION 3.10)
project(RSQ_RMQ_Project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
endif()

include_directories(${PROJECT_SOURCE_DIR})

add_executable(rmq_rsq 
    main.cpp
    benchmark.cpp
)

target_compile_options(rmq_rsq PRIVATE -Wall -Wextra)
