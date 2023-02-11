cmake_minimum_required(VERSION 3.24)
project(strategy_backtesting)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
#include_directories(src/data)
#include_directories(src/data/processor)
#include_directories(src/data/provider)
#include_directories(src/strategy)
#include_directories(src/third_party)
#include_directories(src/third_party/fast-cpp-csv-parser-master)

add_executable(strategy_backtesting
        src/data/processor/CsvProcessor.cpp
        src/data/processor/CsvProcessor.h
        src/data/processor/Processor.h
        src/data/provider/InvestingCom.h
        src/strategy/Strategy.h
        src/third_party/fast-cpp-csv-parser-master/csv.h
        src/main.cpp
        src/data/processor/Processor.cpp
        src/strategy/SimpleRebalance.h
        src/Portfolio.h
        src/Portfolio.cpp
        src/Utilities.h src/Utilities.cpp)
