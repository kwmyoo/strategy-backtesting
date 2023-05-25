//
// Created by Kun Woo Yoo on 2023/05/09.
//

#ifndef STRATEGY_BACKTESTING_HISTORICALDATA_H
#define STRATEGY_BACKTESTING_HISTORICALDATA_H

#include <memory>
#include <vector>

#include "Utilities.h"

typedef std::vector<std::unique_ptr<Period>> AssetData;

class HistoricalData {
 public:
  std::vector<AssetData> data_;

  void addAssetData(const std::string& symbol, std::time_t from, std::time_t to);

  double getAssetPriceAtPeriod(int assetNum, int period);
};


#endif //STRATEGY_BACKTESTING_HISTORICALDATA_H
