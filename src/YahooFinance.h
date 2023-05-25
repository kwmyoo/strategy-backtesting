//
// Created by Kun Woo Yoo on 2023/05/03.
//

#ifndef STRATEGY_BACKTESTING_YAHOOFINANCE_H
#define STRATEGY_BACKTESTING_YAHOOFINANCE_H

#include <sstream>
#include <string>

#include "curl_utils.hpp"
#include "HistoricalData.h"
#include "Utilities.h"
#include "Portfolio.h"
#include "third_party/fast-cpp-csv-parser-master/csv.h"

typedef std::vector<std::unique_ptr<Period>> AssetData;

struct YFSymbols {
  static constexpr auto TIGER_SNP500_ETF = "360750.KS";
  static constexpr auto KODEX_KOSPI_ETF = "278530.KS";
  static constexpr auto TIGER_US_BONDS_ETF = "305080.KS";
  static constexpr auto KOSEF_KOREA_BONDS_ETF = "148070.KS";

  static constexpr auto MICROSOFT = "MSFT";
  static constexpr auto BERKSHIRE_HATHAWAY = "BRK-B";
  static constexpr auto EXXON = "XOM";
  static constexpr auto SHELL = "SHEL";
};

class YahooFinance {
 public:
  static AssetData getAssetData(const std::string& symbol, std::time_t from, std::time_t to);

  static std::vector<double> getData(const std::string& symbol, std::time_t from, std::time_t to);
};


#endif //STRATEGY_BACKTESTING_YAHOOFINANCE_H
