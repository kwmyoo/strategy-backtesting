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

//  std::vector<std::string> symbols;
//  symbols.push_back(YFSymbols::TIGER_SNP500_ETF);
//  symbols.push_back(YFSymbols::KODEX_KOSPI_ETF);
//  symbols.push_back(YFSymbols::TIGER_US_BONDS_ETF);
//  symbols.push_back(YFSymbols::KOSEF_KOREA_BONDS_ETF);
//
//  Backtest backtest(
//      std::make_unique<SimpleRebalance>(),
//      1000000000.0,
//      symbols,
//      "2023-01-01", "2023-09-01"
//  );
//  std::shared_ptr<StrategyInput> input = std::make_shared<SimpleRebalanceInput>(&backtest);

//  std::vector<std::string> symbols;
//  symbols.push_back(YFSymbols::EXXON);
//  symbols.push_back(YFSymbols::SHELL);
//
//  Backtest backtest(
//      std::make_unique<PairTrading>(YFSymbols::EXXON,
//                                    YFSymbols::SHELL,
//                                    "2021-01-01",
//                                    "2021-12-31",
//                                    1.0),
//      1000000000.0,
//      symbols,
//      "2022-01-01", "2022-12-31"
//  );
//  std::shared_ptr<StrategyInput> input = std::make_shared<PairTradingInput>(&backtest);


  backtest.strategyInput_ = std::move(input);
  backtest.execute();

  std::cout << "Final return: " << backtest.totalBalance_ << std::endl;
}
