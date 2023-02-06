//
// Created by Kun Woo Yoo on 2023/02/04.
//

#ifndef STRATEGY_BACKTESTING_SIMPLEREBALANCE_H
#define STRATEGY_BACKTESTING_SIMPLEREBALANCE_H

#include "strategy/Strategy.h"

class SimpleRebalance : public Strategy {
 public:
  SimpleRebalance(long initial_amount);

  void Rebalance(int period) override;
};


#endif //STRATEGY_BACKTESTING_SIMPLEREBALANCE_H
