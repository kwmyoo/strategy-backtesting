//
// Created by Kun Woo Yoo on 2023/01/31.
//

#include <memory>
#include <iostream>

#include "Backtest.h"
#include "YahooFinance.h"

#include "spot.hpp"
#include "time_utils.hpp"
#include "strategy/PairTrading.h"
#include "strategy/SimpleRebalance.h"

int main(int argc, char** argv) {
  Backtest backtest(
      std::make_unique<PairTrading>(
          YFSymbols::TIGER_US_BONDS_ETF,
          YFSymbols::KOSEF_KOREA_BONDS_ETF,
          dateToEpoch("2021-01-01"),
          dateToEpoch("2021-12-31"),
          1.0),
      100000000);

  std::vector<std::string> symbols;
//  symbols.push_back(YFSymbols::TIGER_SNP500_ETF);
//  symbols.push_back(YFSymbols::KODEX_KOSPI_ETF);
  symbols.push_back(YFSymbols::TIGER_US_BONDS_ETF);
  symbols.push_back(YFSymbols::KOSEF_KOREA_BONDS_ETF);

  backtest.initialize(symbols, dateToEpoch("2022-01-01"), dateToEpoch("2022-12-31"));
  backtest.execute();

  std::cout << "Final return: " << backtest.getBalance() << std::endl;
}
