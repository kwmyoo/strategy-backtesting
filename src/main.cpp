//
// Created by Kun Woo Yoo on 2023/01/31.
//

#include <memory>
#include <iostream>

#include "Backtest.h"
#include "YahooFinance.h"

#include "spot.hpp"
#include "strategy/PairTrading.h"
#include "strategy/MovingAverageCrossover.h"
#include "strategy/SimpleRebalance.h"

int main(int argc, char** argv) {
  std::vector<std::string> symbols;
  symbols.push_back(YFSymbols::SNP_500);

  Backtest backtest(
      std::make_unique<MovingAverageCrossover>(),
      1000000000.0,
      symbols,
      "2012-01-01", "2023-08-01"
  );
  std::shared_ptr<StrategyInput> input = std::make_shared<MovingAverageCrossoverInput>(&backtest);
  backtest.strategyInput_ = std::move(input);
  backtest.execute();

  std::cout << "Final return: " << backtest.totalBalance_ << std::endl;
}
