//
// Created by Kun Woo Yoo on 2023/02/04.
//

#ifndef STRATEGY_BACKTESTING_SIMPLEREBALANCE_H
#define STRATEGY_BACKTESTING_SIMPLEREBALANCE_H

#include "Strategy/Strategy.h"

class SimpleRebalance : public Strategy {
 public:
  int operator()(int ratio) override {
    return ratio;
  }
};

#endif //STRATEGY_BACKTESTING_SIMPLEREBALANCE_H
