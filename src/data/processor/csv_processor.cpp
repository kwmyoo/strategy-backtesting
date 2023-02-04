//
// Created by Kun Woo Yoo on 2023/01/28.
//


#include <memory>
#include <string>
#include <utility>

#include "utilities.h"
#include "data/processor/csv_processor.h"
#include "third_party/fast-cpp-csv-parser-master/csv.h"
#include "data/provider/investing_com.h"

CsvProcessor::CsvProcessor() {
  file_type_ = FileType::CSV;
  date_orientation_ = DateOrientation::INVERSED;
}

PeriodQueue CsvProcessor::Process(const std::string& file_name) {
  io::CSVReader<2> in(file_name);
  in.read_header(io::ignore_no_column, "Time", "Price");

  std::string time_string;
  std::string price_string;
  PeriodQueue periods;

  while (in.read_row(time_string, price_string)) {
    periods.emplace_back(std::make_unique<InvestingComPeriod>(Time{time_string}, Price{price_string}));
  }

  return periods;
}