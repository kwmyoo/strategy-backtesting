//
// Created by Kun Woo Yoo on 2023/05/09.
//

#ifndef STRATEGY_BACKTESTING_BACKTEST_H
#define STRATEGY_BACKTESTING_BACKTEST_H

#include <vector>
#include <string>

#include "strategy/Strategy.h"
#include "HistoricalData.h"
#include "Portfolio.h"
#include "Utilities.h"

class Backtest {
 public:
  Backtest(StrategyFn&& strategyFn,
           double initialBalance,
           const std::vector<std::string>& assetNames,
           const char* fromStr, const char* toStr);

  Asset& getAsset(int assetNum);

  const std::string& getAssetNameAtIndex(int index);

  void sellAssetsAtPeriod(int period);

  void buyAssetsAtPeriod(int period);

  void getCurrentPrices(int period);

  // change ratio for each asset
  void adjustRatio(std::vector<double>& prices, int period);

  void execute();

  StrategyFn strategyFn_;

  std::shared_ptr<StrategyInput> strategyInput_;

  HistoricalData historicalData_;

  Portfolio portfolio_;

  std::vector<double> currentPrices_;

  std::vector<int> ratios_;

  int numAssets_;

  int numPeriods_;

  double totalBalance_;

  const char* fromStr_;

  const char* toStr_;
};


#endif //STRATEGY_BACKTESTING_BACKTEST_H
