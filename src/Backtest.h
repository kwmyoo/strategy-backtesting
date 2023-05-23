//
// Created by Kun Woo Yoo on 2023/05/09.
//

#ifndef STRATEGY_BACKTESTING_BACKTEST_H
#define STRATEGY_BACKTESTING_BACKTEST_H

#include <vector>
#include <string>

#include "HistoricalData.h"
#include "Portfolio.h"
#include "Utilities.h"

class Backtest {
 public:
  Backtest(StrategyFn&& strategyFn, double initialBalance) :
      portfolio_(std::move(strategyFn), initialBalance) {};

  void initialize(const std::vector<std::string>& assetNames, std::time_t from, std::time_t to);

  Asset& getAsset(int assetNum);

  void sellAssetsAtPeriod(int period);

  void buyAssetsAtPeriod(int period);

  void execute();

  long getBalance();

 private:
  HistoricalData historicalData_;

  Portfolio portfolio_;

  int numAssets;

  int numPeriods;
};


#endif //STRATEGY_BACKTESTING_BACKTEST_H
