//
// Created by Kun Woo Yoo on 2023/01/31.
//

#include <memory>
#include <iostream>

#include "Utilities.h"
#include "data/processor/Processor.h"
#include "data/processor/CsvProcessor.h"

int main() {
  std::unique_ptr<Processor> processor = Processor::CreateProcessor(FileType::CSV);
  HistoricalData periods = processor->Process("../Data/snp500.csv");

}
