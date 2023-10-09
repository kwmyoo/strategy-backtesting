//
// Created by Kun Woo Yoo on 2023/01/31.
//

#include <memory>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <boost/program_options.hpp>

#include "Backtest.h"
#include "YahooFinance.h"

#include "strategy/PairTrading.h"
#include "strategy/MeanReversion.h"
#include "strategy/MovingAverageCrossover.h"
#include "strategy/SimpleRebalance.h"

namespace po = boost::program_options;

/*
 * Example:
 * ./strategy_backtesting -s pairtrading -f 2022-01-01 -t 2022-12-31 -b 100000000.0 -i XOM SHEL
 */
int main(int argc, char** argv) {
  po::options_description desc{"Options"};
  desc.add_options()
      ("help,h", "Help screen")
      ("strategy,s", po::value<std::string>(), "Strategy")
      ("from,f", po::value<std::string>(), "Date from")
      ("to,t", po::value<std::string>(), "Date to")
      ("balance,b", po::value<double>(), "Initial balance")
      ("ticker,i", po::value<std::vector<std::string>>()->multitoken(), "tickers");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  std::string strategy, from, to;
  std::vector<std::string> symbols;
  double balance;
  if (vm.count("strategy")) {
    strategy = vm["strategy"].as<std::string>();
  } else {
    std::cout << "Error: strategy should be specified" << std::endl;
    std::cout << desc << std::endl;
    return 0;
  }
  if (vm.count("from")) {
    from = vm["from"].as<std::string>();
  } else {
    std::cout << "Error: date from should be specified" << std::endl;
    std::cout << desc << std::endl;
    return 0;
  }
  if (vm.count("to")) {
    to = vm["to"].as<std::string>();
  } else {
    std::cout << "Error: date to should be specified" << std::endl;
    std::cout << desc << std::endl;
    return 0;
  }
  if (vm.count("balance")) {
    balance = vm["balance"].as<double>();
  } else {
    std::cout << "Error: balance should be specified" << std::endl;
    std::cout << desc << std::endl;
    return 0;
  }
  if (vm.count("ticker")) {
    symbols = vm["ticker"].as<std::vector<std::string>>();
  } else {
    std::cout << "Error: tickers should be specified" << std::endl;
    std::cout << desc << std::endl;
    return 0;
  }

  Backtest* backtest;
  std::unique_ptr<Strategy> strategyPtr;
  std::shared_ptr<StrategyInput> strategyInput;

  if (strategy == "r" ||
      strategy == "R" ||
      strategy == "rebalance" ||
      strategy == "Rebalance") {
    strategyPtr = std::make_unique<SimpleRebalance>();
    backtest = new Backtest(std::move(strategyPtr), balance, symbols, from.c_str(), to.c_str());
    strategyInput = std::make_shared<SimpleRebalanceInput>(backtest);
  } else if (strategy == "mac" ||
             strategy == "MAC" ||
             strategy == "movingaveragecrossover" ||
             strategy == "MovingAverageCrossover") {
    strategyPtr = std::make_unique<MovingAverageCrossover>();
    backtest = new Backtest(std::move(strategyPtr), balance, symbols, from.c_str(), to.c_str());
    strategyInput = std::make_shared<MovingAverageCrossoverInput>(backtest);
  } else if (strategy == "mr" ||
             strategy == "MR" ||
             strategy == "meanreversion" ||
             strategy == "MeanReversion") {
    strategyPtr = std::make_unique<MeanReversion>();
    backtest = new Backtest(std::move(strategyPtr), balance, symbols, from.c_str(), to.c_str());
    strategyInput = std::make_shared<MeanReversionInput>(backtest);
  } else if (strategy == "pt" ||
             strategy == "PT" ||
             strategy == "pairtrading" ||
             strategy == "PairTrading") {
    strategyPtr = std::make_unique<PairTrading>();
    backtest = new Backtest(std::move(strategyPtr), balance, symbols, from.c_str(), to.c_str());
    strategyInput = std::make_shared<PairTradingInput>(backtest);
  } else {
    std::cout << "Strategy should be one of: Rebalance, MeanReversion, MovingAverageCrossover, PairTrading"
              << std::endl;
    return 0;
  }

  backtest->strategyInput_ = std::move(strategyInput);
  backtest->execute();
  std::cout << "Final return: " << backtest->totalBalance_ << std::endl;
  std::cout << std::setprecision(4) << "Rate of return: " << (backtest->totalBalance_ - balance) * 100.0 / balance
            << "%"
            << std::endl;

  delete backtest;

  return 0;
}
