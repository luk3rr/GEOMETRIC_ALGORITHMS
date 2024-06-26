# Filename: CMakeLists.txt
# Created on: November  5, 2023
# Author: Lucas Araújo <araujolucas@dcc.ufmg.br>

# Set default parameters
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(GeometricAlgorithms)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler flags for different build types
IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(EXECUTABLE_NAME "program_debug")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra -pedantic")
ELSE()
    SET(EXECUTABLE_NAME "program")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -pedantic")
ENDIF()

MESSAGE(STATUS "C++ Compiler Flags:${CMAKE_CXX_FLAGS}")

SET(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
SET(UNIT_TEST_DIR ${CMAKE_SOURCE_DIR}/test/unit)
SET(INC_DIR ${CMAKE_SOURCE_DIR}/include)
SET(BENCHMARK_DIR ${CMAKE_SOURCE_DIR}/test/benchmark)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/libs)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release)

# Manager submodules
## DataStructures
SET(DATA_STRUCT_DIR ${CMAKE_SOURCE_DIR}/submodules/data_structures)
AUX_SOURCE_DIRECTORY(${DATA_STRUCT_DIR}/src DATA_STRUCT_PROGRAM)
INCLUDE_DIRECTORIES(${DATA_STRUCT_DIR}/include)
ADD_LIBRARY(DataStructures ${DATA_STRUCT_PROGRAM})

## Sorting Algorithms
SET(SORT_ALG_DIR ${CMAKE_SOURCE_DIR}/submodules/sorting_algorithms)
AUX_SOURCE_DIRECTORY(${SORT_ALG_DIR}/src SORT_ALG_PROGRAM)
INCLUDE_DIRECTORIES(${SORT_ALG_DIR}/include)
ADD_LIBRARY(SortingAlgorithms ${SORT_ALG_PROGRAM})

# Compile root project
## Get all files in the folders SRC_DIR and UNIT_TEST_DIR
AUX_SOURCE_DIRECTORY(${SRC_DIR} PROGRAM)
AUX_SOURCE_DIRECTORY(${UNIT_TEST_DIR} UNIT_TESTS)

INCLUDE_DIRECTORIES(${INC_DIR})
INCLUDE_DIRECTORIES(${INC_DIR}/lib)

# Define the program lib
ADD_LIBRARY(GeometricAlgorithms ${PROGRAM})

# Make executables
ADD_EXECUTABLE(program ${PROGRAM})
ADD_EXECUTABLE(unit_test ${UNIT_TESTS})

# Link libs
TARGET_LINK_LIBRARIES(GeometricAlgorithms DataStructures)
TARGET_LINK_LIBRARIES(SortingAlgorithms DataStructures)
TARGET_LINK_LIBRARIES(GeometricAlgorithms SortingAlgorithms)
TARGET_LINK_LIBRARIES(program GeometricAlgorithms)
TARGET_LINK_LIBRARIES(unit_test GeometricAlgorithms)
