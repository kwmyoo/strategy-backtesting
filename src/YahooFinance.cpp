//
// Created by Kun Woo Yoo on 2023/05/03.
//

#include <vector>

#include "HistoricalData.h"
#include "Portfolio.h"
#include "YahooFinance.h"
#include "third_party/fast-cpp-csv-parser-master/csv.h"

AssetData YahooFinance::getAssetData(const std::string& symbol, std::time_t from, std::time_t to) {
  std::istringstream csvStream(downloadYahooCsv(symbol, from, to, "1d"));
  auto csvReader = io::CSVReader<2>(symbol, csvStream);
  csvReader.read_header(io::ignore_extra_column, "Date", "Close");
  std::string timeString;
  std::string priceString;
  AssetData periods;

  while (csvReader.read_row(timeString, priceString)) {
    if (!std::isdigit(timeString[0]) || !std::isdigit(priceString[0])) {
      continue;
    }
    periods.emplace_back(std::make_unique<Period>(Time{timeString}, Price{priceString}));
  }

  return periods;
}

std::vector<double> YahooFinance::getData(const std::string& symbol, std::time_t from, std::time_t to) {
  std::istringstream csvStream(downloadYahooCsv(symbol, from, to, "1d"));
  auto csvReader = io::CSVReader<2>(symbol, csvStream);
  csvReader.read_header(io::ignore_extra_column, "Date", "Close");
  std::string timeString;
  std::string priceString;
  std::vector<double> priceData;

  while (csvReader.read_row(timeString, priceString)) {
    if (!std::isdigit(timeString[0]) || !std::isdigit(priceString[0])) {
      continue;
    }
    priceData.emplace_back(std::stod(priceString));
  }

  return priceData;
}