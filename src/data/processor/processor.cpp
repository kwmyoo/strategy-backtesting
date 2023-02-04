//
// Created by Kun Woo Yoo on 2023/02/02.
//

#include "utilities.h"
#include "data/processor/processor.h"
#include "data/processor/csv_processor.h"

std::unique_ptr<Processor> Processor::CreateProcessor(FileType file_type) {
  if (file_type == FileType::CSV) {
    return std::make_unique<CsvProcessor>();
  }

  return std::make_unique<CsvProcessor>();
}