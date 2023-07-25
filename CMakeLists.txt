# configuration
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(runMe VERSION 1.0)

# Find libzip
find_path(ZIP_INCLUDE_DIR NAMES zip.h)
find_library(ZIP_LIBRARY NAMES zip)

# Build myLibrary as a shared object
add_library(myLibrary SHARED myLibrary.cpp)

# Build static libraries
add_library(airplane STATIC airplane.cpp)
add_library(arrivals STATIC arrivals.cpp)
add_library(full_schedule STATIC full_schedule.cpp)
add_library(zip STATIC zip.cpp zip.h)
add_library(signal_handler STATIC signal_handler.cpp)
add_library(pipe_handler STATIC pipe_handler.cpp pipe_handler.h)
add_library(error_handling STATIC error_handling.cpp)

# Create the executable and link the libraries
add_executable(runMe FlightService.cpp)
target_include_directories(runMe PRIVATE ${ZIP_INCLUDE_DIR})

target_link_libraries(runMe PRIVATE airplane arrivals full_schedule signal_handler pipe_handler zip error_handling)

# Link libzip library
target_link_libraries(runMe PRIVATE ${ZIP_LIBRARY})
target_link_libraries(runMe PUBLIC myLibrary)
