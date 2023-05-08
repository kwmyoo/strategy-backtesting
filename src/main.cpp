//
// Created by Kun Woo Yoo on 2023/01/31.
//

#include <memory>
#include <iostream>
#include <stdlib.h>

#include "Portfolio.h"
#include "Utilities.h"
#include "data/processor/Processor.h"
#include "strategy/SimpleRebalance.h"
#include "data/provider/InvestingDotCom.h"

#include "quote.hpp"
#include "spot.hpp"

int main(int argc, char** argv) {
//  std::unique_ptr<Processor> processor = Processor::createProcessor(FileType::CSV);
//  std::string assets[] = {"../data/snp500.csv", "../data/ktb.csv", "../data/kospi.csv", "../data/us_treasury.csv"};
//
//  if (argc != 4) {
//    std::cout << "Wrong number of arguments" << std::endl;
//    std::cout << "Usage: ./strategy_backtesting <initial fund> <start> <duration>" << std::endl;
//    return 1;
//  }
//
//  int initialFund = atoi(argv[1]);
//  Portfolio portfolio{std::make_unique<SimpleRebalance>(), initialFund};
//
//  for (auto& asset: assets) {
//    portfolio.addAsset(processor->process(asset));
//  }
//
//  portfolio.calculateFinalReturn(atoi(argv[2]), atoi(argv[3]));
//  std::cout << "Final return: " << portfolio.totalMoney_ << std::endl;


  InvestingDotCom<2, io::trim_chars<>, io::double_quote_escape<',', '\"'> > hi{};
  Quote* snp500 = new Quote("360750.KS");

// Get the historical spots from Yahoo Finance
  snp500->getHistoricalSpots("2022-12-01", "2022-12-31", "1d");

// Print the spots
  snp500->printSpots();

// Print a spot
  try {
    Spot spot = snp500->getSpot("2022-12-01");
    spot.printSpot();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

// Get the historical EUR/USD rates
  Quote* eurusd = new Quote("EURUSD=X");
  eurusd->getHistoricalSpots("2023-01-01", "2023-01-10", "1d");
  eurusd->printSpots();

// Get the historical EUR/AUD rates
  Quote* euraud = new Quote("EURAUD=X");
  euraud->getHistoricalSpots("2023-01-01", "2023-01-10", "1d");
  euraud->printSpots();

// Free memory
  delete snp500;
  delete eurusd;
  delete euraud;
}
