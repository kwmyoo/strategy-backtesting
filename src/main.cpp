//
// Created by Kun Woo Yoo on 2023/01/31.
//

#include <memory>
#include <iostream>

#include "Portfolio.h"
#include "Utilities.h"
#include "data/processor/Processor.h"
#include "data/processor/CsvProcessor.h"
#include "strategy/SimpleRebalance.h"

int main(int argc, char** argv) {
  std::cout << "aaaa" << std::endl;
  std::unique_ptr<Processor> processor = Processor::createProcessor(FileType::CSV);
  std::cout << "bbbb" << std::endl;

  std::string assets[] = {"../data/snp500.csv", "../data/ktb.csv", "../data/kospi.csv", "../data/us_treasury.csv"};
  std::cout << "cccc" << std::endl;

  Portfolio portfolio{std::make_unique<SimpleRebalance>(), 100000000};
  std::cout << "dddd" << std::endl;

  for (auto& asset: assets) {
    portfolio.addAsset(processor->process(asset));
  }
  std::cout << "eeee" << std::endl;

  portfolio.calculateFinalReturn();

  std::cout << "Final return: " << portfolio.totalMoney_ << std::endl;
}
