//
// Created by Kun Woo Yoo on 2023/01/28.
//

#ifndef STRATEGY_BACKTESTING_CSV_PROCESSOR_H
#define STRATEGY_BACKTESTING_CSV_PROCESSOR_H

#include <deque>
#include <memory>

#include "data/provider/csv_template.h"
#include "data/processor/processor.h"

class CsvProcessor : public Processor {
 public:
  CsvProcessor();

  PeriodQueue Process(const std::string& file_name);
};


#endif //STRATEGY_BACKTESTING_CSV_PROCESSOR_H
