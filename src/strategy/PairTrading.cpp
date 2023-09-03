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

using namespace boost::math::statistics;

PairTradingInput::PairTradingInput(Backtest* backtest)
    : StrategyInput(backtest->ratios_),
      data_(backtest->historicalData_.data_),
      currentPrices_(backtest->numAssets_),
      numAssets_(backtest->numAssets_) {
  currentRatios_[0] = 0;
  currentRatios_[1] = 0;
}

void PairTradingInput::getInputAtPeriodWithRatio(int period) {
  for (int assetNum = 0; assetNum < numAssets_; assetNum++) {
    currentPrices_[assetNum] = data_[assetNum][period]->price_.price();
  }
}

PairTrading::PairTrading(const std::string& symbol1, const std::string& symbol2,
                         const char* fromStr, const char* toStr,
                         double limit) : limit_(limit) {
  std::time_t from = dateToEpoch(fromStr);
  std::time_t to = dateToEpoch(toStr);
  prices_.emplace_back(YahooFinance::getData(symbol1, from, to));
  prices_.emplace_back(YahooFinance::getData(symbol2, from, to));
  assert(prices_[0].size() == prices_[1].size());

  std::cout << "Covariance of the two stocks is: " << getCovariance() << std::endl;
}

double PairTrading::getCovariance() {
  return covariance(prices_[0], prices_[1]);
}

// Calculates ln(s2) = c1*ln(s1) + c0
void PairTrading::calculateHedgeRatio() {
  std::vector<double> symbol1LogPrice;
  std::vector<double> symbol2LogPrice;

  for (int i = 0; i < prices_[0].size(); i++) {
    symbol1LogPrice.push_back(log(prices_[0][i]));
    symbol2LogPrice.push_back(log(prices_[1][i]));
  }

  const auto [c0, c1]
      = simple_ordinary_least_squares(symbol1LogPrice, symbol2LogPrice);

  logPrices_.emplace_back(symbol1LogPrice);
  logPrices_.emplace_back(symbol2LogPrice);
  hedgeRatio_ = c1;
}

void PairTrading::calculateSpreadMeanAndStd() {
  std::vector<double> spread;

  for (int i = 0; i < prices_[0].size(); i++) {
    spread.push_back(logPrices_[1][i] - hedgeRatio_ * logPrices_[0][i]);
  }

  const auto [mean, std] = mean_and_sample_variance(spread);
  spreadMean_ = mean;
  spreadStd_ = std;
}

double PairTrading::calculateZScore(double price1, double price2) {
  double spread = log(price2) - hedgeRatio_ * log(price1);
  return (spread - spreadMean_) / spreadStd_;
}

int PairTrading::operator()(int assetNum, std::shared_ptr<StrategyInput> input) {
  std::shared_ptr<PairTradingInput> newInput =
      std::reinterpret_pointer_cast<PairTradingInput>(input);
  double zScore = calculateZScore(newInput->currentPrices_[0], newInput->currentPrices_[1]);

  if (zScore >= limit_) {
    if (assetNum == 0) {
      return 100;
    } else if (assetNum == 1) {
      return 0;
    }
  } else if (zScore <= -1 * limit_) {
    if (assetNum == 0) {
      return 0;
    } else if (assetNum == 1) {
      return 100;
    }
  }
  std::cout << "ccc" << std::endl;

  return input->currentRatios_[assetNum];
}

