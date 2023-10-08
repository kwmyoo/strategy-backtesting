//
// Created by Kun Woo Yoo on 2023/05/16.
//

#ifndef STRATEGY_BACKTESTING_PAIRTRADING_H
#define STRATEGY_BACKTESTING_PAIRTRADING_H

#include <memory>
#include <string>
#include <vector>

#include "Backtest.h"
#include "strategy/Strategy.h"
#include "HistoricalData.h"
#include "Utilities.h"

class PairTradingInput : public StrategyInput {
 public:
  int numAssets_;

  std::vector<AssetData>& data_;

  std::vector<double> currentPrices_;

  std::vector<std::vector<double>> pastPrices_;

  std::vector<std::vector<double>> logPrices_;

  double hedgeRatio_;

  double spreadMean_;

  double spreadStd_;

  double zScore_;

  double limit_ = 1.0;

  PairTradingInput(Backtest* backtest);

  void getInputAtPeriod(int period) override;

  double getCovariance();

  void calculateHedgeRatio();

  void calculateSpreadMeanAndStd();

  double calculateZScore(double price1, double price2);
};

/*
 * The following algorithm implements pair trading method introduced in
 * https://blog.quantinsti.com/pairs-trading-basics/
 */
class PairTrading : public Strategy {
 public:
  PairTrading() = default;

  int operator()(int assetNum, std::shared_ptr<StrategyInput> input) override;
};


#endif //STRATEGY_BACKTESTING_PAIRTRADING_H
