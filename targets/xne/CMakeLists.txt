cmake_minimum_required(VERSION 3.10)
project(xne VERSION 0.0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE
    -std=c++17 -Wall -pedantic -Wextra -Weffc++)

if(DEFINED ${CMAKE_BUILD_TYPE} AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ggdb -O0)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        XNE_DBG_MODE)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    XNE_VERSION="${PROJECT_VERSION}")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME}/xne.cpp)