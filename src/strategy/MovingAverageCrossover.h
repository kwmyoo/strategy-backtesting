//
// Created by Kun Woo Yoo on 2023/08/22.
//

#ifndef STRATEGY_BACKTESTING_MOVINGAVERAGECROSSOVER_H
#define STRATEGY_BACKTESTING_MOVINGAVERAGECROSSOVER_H

#include <list>

#include "Backtest.h"
#include "strategy/Strategy.h"
#include "HistoricalData.h"
#include "Utilities.h"

enum class MovingAverageStatus {
  INITIAL,
  LONG_TERM_AVERAGE_HIGHER,
  SHORT_TERM_AVERAGE_HIGHER,
  EQUAL
};

constexpr int SHORT_TERM_MA_PERIOD = 50;

constexpr int LONG_TERM_MA_PERIOD = 200;

class MovingAverageCrossoverInput : public StrategyInput {
 public:
  AssetData& data_;

  int ratio_;

  double shortTermTotal_;

  double shortTermMovingAverage_;

  double longTermTotal_;

  double longTermMovingAverage_;

  MovingAverageCrossoverInput(Backtest* backtest);

  void getInputAtPeriod(int period) override;
};

/*
 * The following strategy implements a moving average crossover trading strategy.
 * More specifically, it uses golden cross and death cross strategy, which uses 50-day and 200-day simple moving  average for signals.
 */
class MovingAverageCrossover : public Strategy {
 public:
  MovingAverageCrossover();

  int operator()(int assetNum, std::shared_ptr<StrategyInput> input) override;

 private:
  MovingAverageStatus status_;

  MovingAverageStatus getCurrentStatus(double shortTermMovingAverage, double longTermMovingAverage);
};


#endif //STRATEGY_BACKTESTING_MOVINGAVERAGECROSSOVER_H
