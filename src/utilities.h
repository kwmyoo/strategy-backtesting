//
// Created by Kun Woo Yoo on 2023/02/02.
//

#ifndef STRATEGY_BACKTESTING_UTILITIES_H
#define STRATEGY_BACKTESTING_UTILITIES_H

#include <deque>
#include <memory>

#include "data/provider/csv_template.h"

enum class FileType {
  CSV
};

enum class DateOrientation {
  NORMAL, // small to big
  INVERSED // big to small
};

typedef std::deque<std::unique_ptr<Period>> PeriodQueue;

#endif //STRATEGY_BACKTESTING_UTILITIES_H
