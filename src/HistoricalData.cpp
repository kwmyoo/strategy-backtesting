//
// Created by Kun Woo Yoo on 2023/05/09.
//

#include <string>

#include "HistoricalData.h"
#include "YahooFinance.h"

void HistoricalData::addAssetData(const std::string& symbol, std::time_t from, std::time_t to) {
  data_.emplace_back(YahooFinance::getAssetData(symbol, from, to));
}

double HistoricalData::getAssetPriceAtPeriod(int assetNum, int period) {
  return data_[assetNum][period]->price_.price();
}
