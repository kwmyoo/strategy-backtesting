//
// Created by Kun Woo Yoo on 2023/02/06.
//

#ifndef STRATEGY_BACKTESTING_PORTFOLIO_H
#define STRATEGY_BACKTESTING_PORTFOLIO_H

#include <utility>
#include <vector>

#include "Utilities.h"
#include "strategy/Strategy.h"

typedef std::vector<std::unique_ptr<Period>> HistoricalData;

struct Asset {
  std::string name_;

  Asset(const std::string& name) : name_(name) {}

  Asset(Asset&& other) : name_(std::move(other.name_)) {}
};

class PortfolioAsset {
 public:
  PortfolioAsset(const std::string& name, bool normalOrientation)
      : asset_(name), ratio_(0), quantity_(0), price_(0), normalOrientation_(normalOrientation) {}

  PortfolioAsset(PortfolioAsset&& other)
      : asset_(std::move(other.asset_)),
        historicalData_(std::move(other.historicalData_)),
        ratio_(other.ratio_),
        normalOrientation_(other.normalOrientation_) {}

  int setCurrentPrice(int index);

  int getAllocatedMoney(int total);

  int buy(int allocated); // buy as much asset as possible w.r.t. current price and given total money, return spent

  int sell(); // sell all assets and return money

  HistoricalData historicalData_;

  friend class Portfolio;

 private:
  Asset asset_;

  bool normalOrientation_;

  int ratio_; // number between 0 - 100 (percentage)

  int quantity_;

  int price_;
};

class Portfolio {
 public:
  Portfolio(StrategyFn&& strategyFn, long totalMoney)
      : strategyFn_(std::move(strategyFn)),
        totalMoney_(totalMoney) {}

  void addAsset(PortfolioAsset&& portfolioAsset);

  void adjustRatio(); // change ratio for each PortfolioAsset

  void calculateFinalReturn(); // calculateFinalReturn the portfolio according to the adjusted ratio

  long totalMoney_;

 private:
  StrategyFn strategyFn_;

  std::vector<PortfolioAsset> portfolioAssets_;
};

#endif //STRATEGY_BACKTESTING_PORTFOLIO_H
