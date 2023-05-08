//
// Created by Kun Woo Yoo on 2023/05/03.
//

#ifndef STRATEGY_BACKTESTING_YAHOOFINANCE_H
#define STRATEGY_BACKTESTING_YAHOOFINANCE_H

#include <sstream>
#include <string>

#include "curl_utils.hpp"
#include "Utilities.h"
#include "Portfolio.h"
#include "third_party/fast-cpp-csv-parser-master/csv.h"

struct YFSymbols {
  static constexpr auto TIGER_SNP500_ETF = "360750.KS";
};

class YahooFinance {
 public:
  PortfolioAsset getAssetData(const std::string& symbol, std::time_t from, std::time_t to);
};


#endif //STRATEGY_BACKTESTING_YAHOOFINANCE_H
