//
// Created by Kun Woo Yoo on 2023/02/02.
//

#include "Utilities.h"
#include "data/processor/Processor.h"
#include "data/processor/CsvProcessor.h"

std::unique_ptr<Processor> Processor::createProcessor(FileType fileType) {
  if (fileType == FileType::CSV) {
    return std::make_unique<CsvProcessor>();
  }

  return std::make_unique<CsvProcessor>();
}