cmake_minimum_required(VERSION 3.24)
project(strategy_backtesting)

set(CMAKE_CXX_STANDARD 17)
set(CURL_PATH "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr")
set(YAHOO_FINANCE "src/third_party/yahoo-finance")
set(HOMEBREW_PATH "/opt/homebrew/opt")

include_directories(src)
include_directories(src/third_party/yahoo-finance/src)

find_library(
        LIB_CURL
        NAMES
        curl
        PATHS
        ${CURL_PATH}/lib
)

find_package(
        Boost
        1.18.0
        REQUIRED
)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(src/third_party/yahoo-finance)

add_executable(strategy_backtesting
        src/strategy/Strategy.h
        src/third_party/fast-cpp-csv-parser-master/csv.h
        src/main.cpp
        src/Portfolio.h
        src/Portfolio.cpp
        src/Utilities.h src/Utilities.cpp
        src/YahooFinance.cpp
        src/YahooFinance.h
        src/Backtest.cpp
        src/Backtest.h
        src/HistoricalData.cpp
        src/HistoricalData.h src/strategy/PairTrading.cpp src/strategy/PairTrading.h src/strategy/MovingAverageCrossover.cpp src/strategy/MovingAverageCrossover.h)

target_link_libraries(strategy_backtesting PRIVATE ${LIB_CURL})
target_include_directories(strategy_backtesting SYSTEM PRIVATE "${CURL_PATH}/include/curl")

target_link_libraries(strategy_backtesting PRIVATE yahoo-finance)
TARGET_LINK_LIBRARIES(strategy_backtesting LINK_PUBLIC ${Boost_LIBRARIES})