//
// Created by Kun Woo Yoo on 2023/01/28.
//

#ifndef STRATEGY_BACKTESTING_CSV_PROCESSOR_H
#define STRATEGY_BACKTESTING_CSV_PROCESSOR_H

#include "processor.h"

class CsvProcessor : public Processor {
 public:
  CsvProcessor();

  void process();
};


#endif //STRATEGY_BACKTESTING_CSV_PROCESSOR_H
