//
// Created by Kun Woo Yoo on 2023/02/04.
//

#ifndef STRATEGY_BACKTESTING_SIMPLEREBALANCE_H
#define STRATEGY_BACKTESTING_SIMPLEREBALANCE_H

#include "Backtest.h"
#include "strategy/Strategy.h"

class SimpleRebalanceInput : public StrategyInput {
 public:
  SimpleRebalanceInput(Backtest* backtest) : StrategyInput(backtest->ratios_) {
    for (auto& ratio: currentRatios_) {
      ratio = 100 / backtest->numAssets_;
    }
  }

  void getInputAtPeriod(int period) override {
    StrategyInput::getInputAtPeriod(period);
  }
};

class SimpleRebalance : public Strategy {
 public:
  int operator()(int assetNum, std::shared_ptr<StrategyInput> input) override {
    return input->currentRatios_[assetNum];
  }
};

#endif //STRATEGY_BACKTESTING_SIMPLEREBALANCE_H
