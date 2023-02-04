cmake_minimum_required(VERSION 3.24)
project(strategy_backtesting)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
#include_directories(src/data)
#include_directories(src/data/processor)
#include_directories(src/data/provider)
#include_directories(src/strategies)
#include_directories(src/third_party)
#include_directories(src/third_party/fast-cpp-csv-parser-master)

add_executable(strategy_backtesting
        src/data/processor/csv_processor.cpp
        src/data/processor/csv_processor.h
        src/data/processor/processor.h
        src/data/provider/investing_com.h
        src/strategies/simple_rebalance.cpp
        src/strategies/simple_rebalance.h
        src/strategies/strategy.h
        src/third_party/fast-cpp-csv-parser-master/csv.h
        src/main.cpp
        src/data/provider/csv_template.h src/data/processor/processor.cpp)
