cmake_minimum_required (VERSION 3.10)

# Define the project
project(advisorbot)

# Following the dicussion on allowed C++ version here:
# https://www.coursera.org/learn/uol-object-oriented-programming/discussions/groups/7OvPlihdEe2VsgoeiZ5qVw/threads/im0JLU7XEe2vVg6vl34jZQ
set(CMAKE_CXX_STANDARD 17)

# Add definition for libraries
add_library(CSVReader src/CSVReader.cpp)
add_library(ApplicationMain src/ApplicationMain.cpp)
add_library(OrderBook src/OrderBook.cpp)
add_library(OrderBookEntry src/OrderBookEntry.cpp)
add_library(Wallet src/Wallet.cpp)
add_library(Commands-Help src/commands/Help.cpp)

# Definition for the advisorbot binary
add_executable(advisorbot src/main.cpp)
target_link_libraries(advisorbot CSVReader ApplicationMain OrderBook OrderBookEntry Wallet Commands-Help)

# Copy CSV data file to build directory
configure_file(data/20200601.csv 20200601.csv COPYONLY)
