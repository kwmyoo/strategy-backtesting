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

  int quantity_;

  int price_;

  friend class Portfolio;

  explicit Asset(const std::string& name)
      : name_(name), quantity_(0), price_(0) {}

  Asset(Asset&& other)
      : name_(std::move(other.name_)),
        quantity_(other.quantity_),
        price_(other.price_) {}

  double getAllocatedMoney(double total, int ratio) const;

  // buy as much asset as possible w.r.t. current price and given total money, return spent
  double buy(double allocated, double price);

  // sell all assets_ and return money
  double sell();
};

class Portfolio {
 public:
  std::vector<Asset> assets_; // assume that all historical data have same length

  Portfolio() {}

  void addAsset(Asset&& portfolioAsset);
};

#endif //STRATEGY_BACKTESTING_PORTFOLIO_H
