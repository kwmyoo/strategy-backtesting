#ifndef STRATEGY_BACKTESTING_STRATEGY_H_
#define STRATEGY_BACKTESTING_STRATEGY_H_

#include <string>
#include <memory>
#include <iomanip>
#include <sstream>
#include <tuple>
#include <time.h>
#include <ctime>
#include <vector>

//#include "Backtest.h"
#include "Utilities.h"

class StrategyInput {
 public:
  std::vector<int>& currentRatios_;

  int period_;

  StrategyInput(std::vector<int>& ratios) : currentRatios_(ratios) {}

  virtual void getInputAtPeriod(int period) {
    period_ = period;
  }
};


//template<typename T>
class Strategy {
 public:
  virtual ~Strategy() = default;

//  virtual int operator()(int i, int ratio, std::vector<double>& prices) = 0;
  virtual int operator()(int assetNum, std::shared_ptr<StrategyInput> input) = 0;
};

typedef std::unique_ptr<Strategy> StrategyFn;

#endif // STRATEGY_BACKTESTING_STRATEGY_H_