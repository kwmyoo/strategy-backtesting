// Created by Kun Woo Yoo on 2023/05/09.


#include <cassert>
#include <utility>

#include "time_utils.hpp"
#include "Backtest.h"

Backtest::Backtest(StrategyFn&& strategyFn,
                   double initialBalance,
                   const std::vector<std::string>& assetNames,
                   const char* fromStr, const char* toStr)
    : strategyFn_(std::move(strategyFn)),
      numAssets_(0),
      numPeriods_(0),
      totalBalance_(initialBalance) {
  std::time_t from = dateToEpoch(fromStr);
  std::time_t to = dateToEpoch(toStr);

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

  ratios_ = std::vector<int>(numAssets_);
  currentPrices_ = std::vector<double>(numAssets_, 0.0);
}

Asset& Backtest::getAsset(int assetNum) {
  return portfolio_.assets_[assetNum];
}

void Backtest::sellAssetsAtPeriod(int period) {
  for (int assetNum = 0; assetNum < numAssets_; assetNum++) {
    Asset& asset = getAsset(assetNum);
    int quantity = asset.sell();
    totalBalance_ += quantity * currentPrices_[assetNum];
  }
}

void Backtest::buyAssetsAtPeriod(int period) {
  for (int assetNum = 0; assetNum < numAssets_; assetNum++) {
    Asset& asset = getAsset(assetNum);
    double allocated = asset.getAllocatedMoney(totalBalance_, ratios_[assetNum]);
    totalBalance_ -= asset.buy(allocated, currentPrices_[assetNum]);
  }
}

void Backtest::getCurrentPrices(int period) {
  for (int assetNum = 0; assetNum < numAssets_; assetNum++) {
    double price = historicalData_.getAssetPriceAtPeriod(assetNum, period);
    currentPrices_[assetNum] = price;
  }
}

void Backtest::adjustRatio(std::vector<double>& prices, int period) {
  strategyInput_->getInputAtPeriod(period);

  for (int assetNum = 0; assetNum < numAssets_; assetNum++) {
    ratios_[assetNum] = (*strategyFn_)(assetNum, strategyInput_);
  }
}

void Backtest::execute() {
  for (int period = 0; period < numPeriods_ - 1; period++) {
    getCurrentPrices(period);
    adjustRatio(currentPrices_, period);
    sellAssetsAtPeriod(period);
    buyAssetsAtPeriod(period);
  }

  sellAssetsAtPeriod(numPeriods_ - 1);
}