//
// Created by Kun Woo Yoo on 2023/05/09.
//

#include <cassert>

#include "Backtest.h"

void Backtest::initialize(const std::vector<std::string>& assetNames, std::time_t from, std::time_t to) {
  numAssets = assetNames.size();
  for (int i = 0; i < numAssets; i++) {
    portfolio_.addAsset(Asset{assetNames[i]});
    historicalData_.addAssetData(assetNames[i], from, to);

    std::cout << "num periods: " << historicalData_.data_[i].size() << std::endl;
    if (numPeriods == 0) {
      numPeriods = historicalData_.data_[i].size();
    } else {
      std::cout << "numPeriods: " << numPeriods << std::endl;
      assert(numPeriods == historicalData_.data_[i].size());
    }
  }
}

Asset& Backtest::getAsset(int assetNum) {
  return portfolio_.assets_[assetNum];
}

void Backtest::sellAssetsAtPeriod(int period) {
  for (int assetNum = 0; assetNum < numAssets; assetNum++) {
    Asset& asset = getAsset(assetNum);
    int quantity = asset.sell();
    int price = historicalData_.getAssetPriceAtPeriod(assetNum, period);
    portfolio_.balance_ += quantity * price;
  }
}

void Backtest::buyAssetsAtPeriod(int period) {
  double totalBalance = portfolio_.balance_;
  for (int assetNum = 0; assetNum < numAssets; assetNum++) {
    Asset& asset = getAsset(assetNum);
    int allocated = asset.getAllocatedMoney(totalBalance);
    int price = historicalData_.getAssetPriceAtPeriod(assetNum, period);
    portfolio_.balance_ -= asset.buy(allocated, price);
  }
}

void Backtest::execute() {
  for (int period = 0; period < numPeriods - 1; period++) {
    portfolio_.adjustRatio();
    sellAssetsAtPeriod(period);
    buyAssetsAtPeriod(period);
  }

  sellAssetsAtPeriod(numPeriods - 1);
}

long Backtest::getBalance() {
  return portfolio_.balance_;
}