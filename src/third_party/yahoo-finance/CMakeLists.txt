cmake_minimum_required(VERSION 3.11.0)
project(yahoo-finance CXX)

# Enable C+11
set(CMAKE_CXX_STANDARD 17)

# Library source files
file(GLOB LIB_SOURCES src/*.cpp)
file(GLOB LIB_HEADERS src/*.hpp)
add_library(yahoo-finance ${LIB_SOURCES} ${LIB_HEADERS})
target_include_directories(yahoo-finance PUBLIC ${LIB_HEADERS})

# Build documentation
add_subdirectory(doc)

# Create example executable
add_executable(example src/example.cpp)
target_link_libraries(example yahoo-finance curl)

# Build tests and enable CTest
enable_testing()
add_subdirectory(test)
