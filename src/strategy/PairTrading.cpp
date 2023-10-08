//
// Created by Kun Woo Yoo on 2023/05/16.
//

#include <boost/math/statistics/bivariate_statistics.hpp>
#include <boost/math/statistics/linear_regression.hpp>
#include <cassert>
#include <math.h>
#include <stdio.h>

#include "PairTrading.h"
#include "YahooFinance.h"
#include "time_utils.hpp"
#include "Utilities.h"

using namespace boost::math::statistics;

PairTradingInput::PairTradingInput(Backtest* backtest)
    : StrategyInput(backtest->ratios_),
      data_(backtest->historicalData_.data_),
      currentPrices_(backtest->numAssets_),
      numAssets_(backtest->numAssets_) {
  currentRatios_[0] = 0;
  currentRatios_[1] = 0;

  std::time_t to = dateToEpoch(backtest->fromStr_);
  std::time_t from = to - YEAR_IN_SECONDS;
  pastPrices_.emplace_back(YahooFinance::getData(backtest->getAssetNameAtIndex(0), from, to));
  pastPrices_.emplace_back(YahooFinance::getData(backtest->getAssetNameAtIndex(1), from, to));
  assert(pastPrices_[0].size() == pastPrices_[1].size());
  std::cout << "Covariance of the two stocks is: " << getCovariance() << std::endl;

  calculateHedgeRatio();
}

void PairTradingInput::getInputAtPeriod(int period) {
  for (int assetNum = 0; assetNum < numAssets_; assetNum++) {
    currentPrices_[assetNum] = data_[assetNum][period]->price_.price();
  }

  zScore_ = calculateZScore(currentPrices_[0], currentPrices_[1]);
}

double PairTradingInput::getCovariance() {
  return covariance(pastPrices_[0], pastPrices_[1]);
}

// Calculates ln(s2) = c1*ln(s1) + c0
void PairTradingInput::calculateHedgeRatio() {
  std::vector<double> symbol1LogPrice;
  std::vector<double> symbol2LogPrice;

  for (int i = 0; i < pastPrices_[0].size(); i++) {
    symbol1LogPrice.push_back(log(pastPrices_[0][i]));
    symbol2LogPrice.push_back(log(pastPrices_[1][i]));
  }

  const auto [c0, c1]
      = simple_ordinary_least_squares(symbol1LogPrice, symbol2LogPrice);

  logPrices_.emplace_back(symbol1LogPrice);
  logPrices_.emplace_back(symbol2LogPrice);
  hedgeRatio_ = c1;
}

void PairTradingInput::calculateSpreadMeanAndStd() {
  std::vector<double> spread;

  for (int i = 0; i < pastPrices_[0].size(); i++) {
    spread.push_back(logPrices_[1][i] - hedgeRatio_ * logPrices_[0][i]);
  }

  const auto [mean, std] = mean_and_sample_variance(spread);
  spreadMean_ = mean;
  spreadStd_ = std;
}

double PairTradingInput::calculateZScore(double price1, double price2) {
  double spread = log(price2) - hedgeRatio_ * log(price1);
  return (spread - spreadMean_) / spreadStd_;
}

int PairTrading::operator()(int assetNum, std::shared_ptr<StrategyInput> input) {
  std::shared_ptr<PairTradingInput> newInput =
      std::reinterpret_pointer_cast<PairTradingInput>(input);

  if (newInput->zScore_ >= newInput->limit_) {
    if (assetNum == 0) {
      return 100;
    } else if (assetNum == 1) {
      return 0;
    }
  } else if (newInput->zScore_ <= -1 * newInput->limit_) {
    if (assetNum == 0) {
      return 0;
    } else if (assetNum == 1) {
      return 100;
    }
  }

  return newInput->currentRatios_[assetNum];
}

