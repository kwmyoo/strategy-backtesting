//
// Created by Kun Woo Yoo on 2023/02/06.
//
#include <iostream>

#include "Portfolio.h"
#include "Utilities.h"

void PortfolioAsset::setCurrentPrice(int index) {
  price_ = historicalData_[index]->price_.price();
}

int PortfolioAsset::getAllocatedMoney(int total) {
  return (total * ratio_) / 100;
}

int PortfolioAsset::buy(int allocated) {
  quantity_ = allocated / price_;
  return quantity_ * price_;
}

int PortfolioAsset::sell() {
  int result = quantity_ * price_;
  quantity_ = 0;
  return result;
}

void Portfolio::addAsset(PortfolioAsset&& portfolioAsset) {
  portfolioAssets_.emplace_back(std::move(portfolioAsset));
}

void Portfolio::adjustRatio() {
  for (int i = 0; i < portfolioAssets_.size(); i++) {
    PortfolioAsset& portfolioAsset = portfolioAssets_[i];
    portfolioAsset.ratio_ = (*strategyFn_)(i, portfolioAsset.ratio_);
  }
}

void Portfolio::calculateFinalReturn(int start, int duration) {
  int numDate = portfolioAssets_[0].historicalData_.size() - 1;

  for (int i = 0; i < duration - 1; i++) {
    adjustRatio();

    for (auto& portfolioAsset: portfolioAssets_) {
      int index = (portfolioAsset.normalOrientation_) ? start + i : numDate - start - i - 1;
      portfolioAsset.setCurrentPrice(index);
      totalMoney_ += portfolioAsset.sell();
    }

    for (auto& portfolioAsset: portfolioAssets_) {
      int allocated = portfolioAsset.getAllocatedMoney(totalMoney_);
      totalMoney_ -= portfolioAsset.buy(allocated);
    }
  }

  for (auto& portfolioAsset: portfolioAssets_) {
    int index = (portfolioAsset.normalOrientation_) ? start + duration : numDate - start - duration - 2;
    portfolioAsset.setCurrentPrice(index);
    totalMoney_ += portfolioAsset.sell();
  }
}