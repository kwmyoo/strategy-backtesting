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

  double updateShortTermMovingAverage(int i, double price);

  double updateLongTermMovingAverage(int i, double price);

  MovingAverageCrossoverInput(
      Backtest* backtest);

  void getInputAtPeriodWithRatio(int period) override;
};

/*
 * The following strategy implements a moving average crossover trading strategy.
 * More specifically, it uses golden cross strategy, which uses 50-day and 200-day simple moving  average for signals.
 */
class MovingAverageCrossover : public Strategy {
 public:
  MovingAverageCrossover();

  int operator()(int assetNum, std::shared_ptr<StrategyInput> input) override;

 private:
  MovingAverageStatus status_;

  double shortTermTotal_;

  double shortTermMovingAverage_;

  std::list<double> shortTermWindow_;

  double longTermTotal_;

  double longTermMovingAverage_;

  std::list<double> longTermWindow_;

  double updateShortTermMovingAverage(int i, double price);

  double updateLongTermMovingAverage(int i, double price);

  MovingAverageStatus getCurrentStatus(double shortTermMovingAverage, double longTermMovingAverage);
};


#endif //STRATEGY_BACKTESTING_MOVINGAVERAGECROSSOVER_H
