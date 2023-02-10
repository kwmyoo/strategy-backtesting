//
// Created by Kun Woo Yoo on 2023/02/06.
//
#include <iostream>

#include "Portfolio.h"
#include "Utilities.h"

int PortfolioAsset::setCurrentPrice(int index) {
  return price_ = historicalData_[index]->price_.price();
}

int PortfolioAsset::getAllocatedMoney(int total) {
  return total * ratio_ / price_;
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

void Portfolio::calculateFinalReturn() {
  std::cout << "ffff" << std::endl;

  int numDate = portfolioAssets_[0].historicalData_.size();
  std::cout << "gggg" << std::endl;

  for (int i = 0; i < numDate; i++) {
    std::cout << "hhhh" << std::endl;

    adjustRatio();
    std::cout << "iiii" << std::endl;

    for (auto& portfolioAsset: portfolioAssets_) {
      totalMoney_ += portfolioAsset.sell();
      int index = (portfolioAsset.normalOrientation_) ? i : index - i - 1;
      portfolioAsset.setCurrentPrice(index);
    }
    std::cout << "jjjj" << std::endl;

    for (auto& portfolioAsset: portfolioAssets_) {
      int allocated = portfolioAsset.getAllocatedMoney(totalMoney_);
      totalMoney_ -= portfolioAsset.buy(allocated);
    }
  }
}