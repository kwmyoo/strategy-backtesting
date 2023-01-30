//
// Created by Kun Woo Yoo on 2023/01/28.
//

#include <string>

#include "data_processor/processor.h"
#include "data_processor/csv_processor.h"
#include "third_party/fast-cpp-csv-parser-master/csv.h"

CsvProcessor::CsvProcessor() : fileType(FileType.CSV) {
}

void CsvProcessor::process(const std::string& fileName) {
  io::CsvReader<7> in(filename);
  in.read_header("Date", "Price", "Open", "High", "Low", "Vol.", "Change %");
  std::string date;
  int price;
  int open;
  int high;
  int low;
  int vol;
}