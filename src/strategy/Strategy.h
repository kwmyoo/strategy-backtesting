#ifndef STRATEGY_BACKTESTING_STRATEGY_H_
#define STRATEGY_BACKTESTING_STRATEGY_H_

#include "strategy/Strategy.h"
#include <string>
#include <memory>
#include <iomanip>
#include <sstream>
#include <tuple>
#include <time.h>
#include <ctime>
#include <vector>

#include "Utilities.h"

class Strategy {
 public:
  virtual ~Strategy() = default;

  virtual int operator()(int i, int ratio, std::vector<double>& prices) = 0;
};

typedef std::unique_ptr<Strategy> StrategyFn;

#endif // STRATEGY_BACKTESTING_STRATEGY_H_