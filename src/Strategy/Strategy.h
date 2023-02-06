#ifndef STRATEGY_BACKTESTING_STRATEGY_H_
#define STRATEGY_BACKTESTING_STRATEGY_H_

#include <vector>

#include "Utilities.h"
#include "Asset.h"

class AssetManagement {
 public:

 private:
  Asset asset_;

  HistoricalData historical_data_;

  int ratio_; // number between 0 - 100 (percentage)
};

class Portfolio {
 public:
  Portfolio(long total_amount) : total_amount_(total_amount) {}

  void Rebalance(); // change ratio for each AssetManagement

 private:
  std::vector<AssetManagement> asset_managements_;

  long total_amount_;
};

class Strategy {
 public:
  virtual ~Strategy() {}

  virtual void Rebalance(int period) = 0;

  Portfolio portfolio_;
};

#endif // STRATEGY_BACKTESTING_STRATEGY_H_