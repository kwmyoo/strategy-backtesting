//
// Created by Kun Woo Yoo on 2023/02/06.
//

#ifndef STRATEGY_BACKTESTING_PORTFOLIO_H
#define STRATEGY_BACKTESTING_PORTFOLIO_H

#include <algorithm>
#include <iostream>
#include <limits.h>
#include <memory>
#include <utility>
#include <vector>

#include "Utilities.h"
#include "strategy/Strategy.h"

class Asset {
 public:
  std::string name_;

  int ratio_; // number between 0 - 100 (percentage)

  int quantity_;

  int price_;

  friend class Portfolio;

  explicit Asset(const std::string& name)
      : name_(name), ratio_(25), quantity_(0), price_(0) {}

  Asset(Asset&& other)
      : name_(std::move(other.name_)),
        ratio_(other.ratio_),
        quantity_(other.quantity_),
        price_(other.price_) {}

  double getAllocatedMoney(double total) const;

  // buy as much asset as possible w.r.t. current price and given total money, return spent
  double buy(double allocated, double price);

  // sell all assets_ and return money
  double sell();
};

class Portfolio {
 public:
  double balance_;

  StrategyFn strategyFn_;

  std::vector<Asset> assets_; // assume that all historical data have same length

  Portfolio() {}

  Portfolio(StrategyFn&& strategyFn, long totalMoney)
      : strategyFn_(std::move(strategyFn)),
        balance_(totalMoney) {}

  void addAsset(Asset&& portfolioAsset);

  void adjustRatio(std::vector<double>& prices); // change ratio for each Asset
};

#endif //STRATEGY_BACKTESTING_PORTFOLIO_H
