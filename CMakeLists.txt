cmake_minimum_required(VERSION 3.24)
project(strategy_backtesting)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
#include_directories(src/Data)
#include_directories(src/Data/Processor)
#include_directories(src/Data/Provider)
#include_directories(src/Strategy)
#include_directories(src/third_party)
#include_directories(src/third_party/fast-cpp-csv-parser-master)

add_executable(strategy_backtesting
        src/Data/Processor/CsvProcessor.cpp
        src/Data/Processor/CsvProcessor.h
        src/Data/Processor/Processor.h
        src/Data/Provider/InvestingCom.h
        src/Strategy/Strategy.h
        src/third_party/fast-cpp-csv-parser-master/csv.h
        src/main.cpp
        src/Period.h
        src/Data/Processor/Processor.cpp src/Asset.h src/Asset.cpp src/Strategy/SimpleRebalance.h)
