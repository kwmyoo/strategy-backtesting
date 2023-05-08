//
// Created by Kun Woo Yoo on 2023/05/03.
//

#include "YahooFinance.h"
#include "Portfolio.h"
#include "third_party/fast-cpp-csv-parser-master/csv.h"

PortfolioAsset YahooFinance::getAssetData(const std::string& symbol, std::time_t from, std::time_t to) {
  std::istringstream csvStream(downloadYahooCsv(symbol, from, to, "1d"));
  auto csvReader = io::CSVReader<2>(symbol, csvStream);
  csvReader.read_header(io::ignore_extra_column, "Date", "Close");
  std::string timeString;
  std::string priceString;
  HistoricalData periods;

  while (csvReader.read_row(timeString, priceString)) {
    periods.emplace_back(std::make_unique<Period>(Time{timeString}, Price{priceString}));
  }

  PortfolioAsset portfolioAsset(symbol, false);
  portfolioAsset.historicalData_ = std::move(periods);
  return portfolioAsset;
}