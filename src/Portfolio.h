//
// Created by Kun Woo Yoo on 2023/02/06.
//

#ifndef STRATEGY_BACKTESTING_PORTFOLIO_H
#define STRATEGY_BACKTESTING_PORTFOLIO_H

#include <vector>

#include "Asset.h"
#include "Utilities.h"

class PortfolioAsset {
 public:
  PortfolioAsset(PortfolioAsset&& other)
      : asset_(std::move(other.asset_)),
        historical_data_(std::move(other.historical_data_)),
        ratio_(other.ratio_) {}

 private:
  Asset asset_;

  HistoricalData historical_data_;

  int ratio_; // number between 0 - 100 (percentage)
};

class Portfolio {
 public:
  Portfolio(StrategyFn&& _strategyFn, long total_amount)
      : strategyFn(std::move(_strategyFn)),
        total_amount_(total_amount) {}

  void AddAsset(PortfolioAsset&& portfolio_asset);

  void Rebalance(); // change ratio for each PortfolioAsset

 private:
  StrategyFn strategyFn;

  std::vector<PortfolioAsset> portfolio_assets_;

  long total_amount_;
};

#endif //STRATEGY_BACKTESTING_PORTFOLIO_H
