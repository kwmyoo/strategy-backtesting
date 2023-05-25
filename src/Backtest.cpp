//
// Created by Kun Woo Yoo on 2023/05/09.
//

#include <cassert>

#include "Backtest.h"

void Backtest::initialize(const std::vector<std::string>& assetNames, std::time_t from, std::time_t to) {
  numAssets_ = assetNames.size();
  for (int i = 0; i < numAssets_; i++) {
    portfolio_.addAsset(Asset{assetNames[i]});
    historicalData_.addAssetData(assetNames[i], from, to);

    if (numPeriods_ == 0) {
      numPeriods_ = historicalData_.data_[i].size();
    } else {
      assert(numPeriods_ == historicalData_.data_[i].size());
    }
  }

  currentPrices_ = std::vector<double>(numAssets_, 0.0);
}

Asset& Backtest::getAsset(int assetNum) {
  return portfolio_.assets_[assetNum];
}

void Backtest::sellAssetsAtPeriod(int period) {
  for (int assetNum = 0; assetNum < numAssets_; assetNum++) {
    Asset& asset = getAsset(assetNum);
    int quantity = asset.sell();
    portfolio_.balance_ += quantity * currentPrices_[assetNum];
  }
}

void Backtest::buyAssetsAtPeriod(int period) {
  double totalBalance = portfolio_.balance_;
  for (int assetNum = 0; assetNum < numAssets_; assetNum++) {
    Asset& asset = getAsset(assetNum);
    double allocated = asset.getAllocatedMoney(totalBalance);
    portfolio_.balance_ -= asset.buy(allocated, currentPrices_[assetNum]);
  }
}

void Backtest::getCurrentPrices(int period) {
  for (int assetNum = 0; assetNum < numAssets_; assetNum++) {
    double price = historicalData_.getAssetPriceAtPeriod(assetNum, period);
    currentPrices_[assetNum] = price;
  }
}

void Backtest::execute() {
  for (int period = 0; period < numPeriods_ - 1; period++) {
    getCurrentPrices(period);
    portfolio_.adjustRatio(currentPrices_);
    sellAssetsAtPeriod(period);
    buyAssetsAtPeriod(period);
  }

  sellAssetsAtPeriod(numPeriods_ - 1);
}

long Backtest::getBalance() {
  return portfolio_.balance_;
}