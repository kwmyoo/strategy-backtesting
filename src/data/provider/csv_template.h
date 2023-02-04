//
// Created by Kun Woo Yoo on 2023/02/01.
//

#ifndef STRATEGY_BACKTESTING_CSV_TEMPLATE_H
#define STRATEGY_BACKTESTING_CSV_TEMPLATE_H

#include <string>

class Period {
 public:
  virtual ~Period() {}

  virtual std::string ToString() = 0;
};

#endif //STRATEGY_BACKTESTING_CSV_TEMPLATE_H
