cmake_minimum_required(VERSION 3.24)
project(strategy_backtesting)

set(CMAKE_CXX_STANDARD 17)
set(CURL_PATH "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr")
set(YAHOO_FINANCE "src/third_party/yahoo-finance")

include_directories(src)
include_directories(src/third_party/yahoo-finance/src)

find_library(
        LIB_CURL
        NAMES
        curl
        PATHS
        ${CURL_PATH}/lib
)

add_subdirectory(src/third_party/yahoo-finance)

add_executable(strategy_backtesting
        src/data/processor/CsvProcessor.cpp
        src/data/processor/CsvProcessor.h
        src/data/processor/Processor.h
        src/strategy/Strategy.h
        src/third_party/fast-cpp-csv-parser-master/csv.h
        src/main.cpp
        src/data/processor/Processor.cpp
        src/strategy/SimpleRebalance.h
        src/Portfolio.h
        src/Portfolio.cpp
        src/Utilities.h src/Utilities.cpp
        src/YahooFinance.cpp
        src/data/provider/CsvProvider.h)

target_link_libraries(strategy_backtesting PRIVATE ${LIB_CURL})
target_include_directories(strategy_backtesting SYSTEM PRIVATE "${CURL_PATH}/include/curl")

target_link_libraries(strategy_backtesting PRIVATE yahoo-finance)
