#ifndef STRATEGY_BACKTESTING_STRATEGY_H_
#define STRATEGY_BACKTESTING_STRATEGY_H_

#include <vector>

#include "Utilities.h"
#include "Asset.h"
#include "Portfolio.h"

class Strategy {
 public:
  virtual ~Strategy() {}

  virtual int operator()(int ratio) = 0;
};

#endif // STRATEGY_BACKTESTING_STRATEGY_H_