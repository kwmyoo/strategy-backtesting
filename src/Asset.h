//
// Created by Kun Woo Yoo on 2023/02/04.
//

#ifndef STRATEGY_BACKTESTING_ASSET_H
#define STRATEGY_BACKTESTING_ASSET_H

#include "Utilities.h"

class Asset {
 public:
  std::string name_;

  int quantity;

  int price;

  Asset(std::string&& name, HistoricalData&& historical_data);

  int Buy(int total);

  int Sell();
};

#endif //STRATEGY_BACKTESTING_ASSET_H
