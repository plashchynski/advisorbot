cmake_minimum_required (VERSION 3.10)

set(PROJECT_NAME_STR advisorbot)
set(PROJECT_MODULES CSVReader AppMain OrderBook OrderBookEntry LinearRegression)

# Define the project
project(${PROJECT_NAME_STR})

# Following the dicussion on allowed C++ version here:
# https://www.coursera.org/learn/uol-object-oriented-programming/discussions/groups/7OvPlihdEe2VsgoeiZ5qVw/threads/im0JLU7XEe2vVg6vl34jZQ
set(CMAKE_CXX_STANDARD 17)

# Add definition for libraries
add_library(CSVReader src/CSVReader.cpp)
add_library(AppMain src/AppMain.cpp)
add_library(OrderBook src/OrderBook.cpp)
add_library(OrderBookEntry src/OrderBookEntry.cpp)
add_library(LinearRegression src/LinearRegression.cpp)

# Add definition for Boost
find_package(Boost 1.80 REQUIRED COMPONENTS iostreams unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

# Unit tests
add_subdirectory(test)

# Definition for the advisorbot binary
add_executable(advisorbot src/main.cpp)
target_link_libraries(advisorbot ${PROJECT_MODULES} ${Boost_LIBRARIES})

# Copy CSV data file to build directory
configure_file(data/20200601.csv 20200601.csv COPYONLY)
