cmake_minimum_required(VERSION 3.10)
project(test_basic_socket VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE
    -std=c++17 -Wall -pedantic -Wextra -Weffc++)

if(DEFINED ${CMAKE_BUILD_TYPE} AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ggdb -O0)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        XNE_DBG_MODE)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests/include)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/tests/src/test.cpp
    ${PROJECT_SOURCE_DIR}/test.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    xne)
