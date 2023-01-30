#ifndef STRATEGY_BACKTESTING_STRATEGY_H_
#define STRATEGY_BACKTESTING_STRATEGY_H_

class Strategy {
 public:
  virtual ~Strategy() {}

  virtual void rebalance() = 0;
};

#endif // STRATEGY_BACKTESTING_STRATEGY_H_