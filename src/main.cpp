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

int main(int argc, char** argv) {
  std::unique_ptr<Processor> processor = Processor::createProcessor(FileType::CSV);
  std::string assets[] = {"../data/snp500.csv", "../data/ktb.csv", "../data/kospi.csv", "../data/us_treasury.csv"};

  if (argc != 2) {
    std::cout << "Wrong number of arguments" << std::endl;
    std::cout << "Usage: ./strategy_backtesting <initial fund>" << std::endl;
    return 1;
  }

  int initialFund = atoi(argv[1]);
  Portfolio portfolio{std::make_unique<SimpleRebalance>(), initialFund};

  for (auto& asset: assets) {
    portfolio.addAsset(processor->process(asset));
  }

  int duration = portfolio.getShortestDuration();
  portfolio.calculateFinalReturn(duration, 0, duration);
  std::cout << "Final return: " << portfolio.totalMoney_ << std::endl;
}
