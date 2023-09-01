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

  PairTradingInput(Backtest* backtest);

  void getInputAtPeriodWithRatio(int period) override;
};

/*
 * The following algorithm implements pair trading method introduced in
 * https://blog.quantinsti.com/pairs-trading-basics/
 */
class PairTrading : public Strategy {
 public:
  PairTrading(const std::string& symbol1, const std::string& symbol2, std::time_t from, std::time_t to, double limit);

  double getCovariance();

//  double getCointegration();

  void calculateHedgeRatio();

  void calculateSpreadMeanAndStd();

  double calculateZScore(double price1, double price2);

  int operator()(int assetNum, std::shared_ptr<StrategyInput> input) override;

 private:
  std::vector<std::vector<double>> prices_;

  std::vector<std::vector<double>> logPrices_;

  double hedgeRatio_;

  double spreadMean_;

  double spreadStd_;

  double limit_;
};


#endif //STRATEGY_BACKTESTING_PAIRTRADING_H
