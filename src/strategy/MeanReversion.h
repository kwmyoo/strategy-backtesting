//
// Created by Kun Woo Yoo on 2023/09/05.
//

#ifndef STRATEGY_BACKTESTING_MEANREVERSION_H
#define STRATEGY_BACKTESTING_MEANREVERSION_H

#include <list>

#include "Backtest.h"
#include "HistoricalData.h"
#include "strategy/Strategy.h"

constexpr int MOVING_AVERAGE_PERIOD = 200;
constexpr int RSI_PERIOD = 10;

class MeanReversionInput : public StrategyInput {
 public:
  AssetData& data_;

  double currPrice_;

  double movingAverage_;

  double movingAverageTotal_;

  double rsi_;

  double rsiGainTotal_;

  double rsiLossTotal_;

  std::list<double> rsiWindow_;

  MeanReversionInput(Backtest* backtest);

  void getInputAtPeriod(int period) override;
};

/*
 * The following class implements the mean reversion strategy explained in the following link:
 * https://www.tradingwithrayner.com/mean-reversion-trading-strategy/
 */
class MeanReversion : public Strategy {
 public:
  double rsiBuyThreshold_ = 30.0;

  double rsiSellThreshold_ = 40.0;

  int sellPeriodThreshold_ = 10;

  int buyPeriod_; // if buy period < 0, then the portfolio currently does not hold the asset

  MeanReversion();

  int operator()(int assetNum, std::shared_ptr<StrategyInput> input) override;

  bool isBuySignal(std::shared_ptr<MeanReversionInput> input);

  bool isSellSignal(std::shared_ptr<MeanReversionInput> input);
};


#endif //STRATEGY_BACKTESTING_MEANREVERSION_H
