//
// Created by Kun Woo Yoo on 2023/01/31.
//

#include <memory>
#include <iostream>

#include "utilities.h"
#include "data/processor/processor.h"
#include "data/processor/csv_processor.h"

int main() {
  std::unique_ptr<Processor> processor = Processor::CreateProcessor(FileType::CSV);
  PeriodQueue periods = processor->Process("../data/snp500.csv");

}
