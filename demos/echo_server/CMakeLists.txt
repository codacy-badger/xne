cmake_minimum_required(VERSION 3.10)
project(echo_server VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE
    -std=c++17 -Wall -pedantic -Wextra -Weffc++)

if(DEFINED ${CMAKE_BUILD_TYPE} AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ggdb -O0)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include)

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/server.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    xne)
