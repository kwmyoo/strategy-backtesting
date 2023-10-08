//
// Created by Kun Woo Yoo on 2023/09/05.
//

#include <math.h>

#include "MeanReversion.h"

MeanReversionInput::MeanReversionInput(Backtest* backtest)
    : StrategyInput(backtest->ratios_),
      data_(backtest->historicalData_.data_[0]) {
  movingAverage_ = 0.0;
  movingAverageTotal_ = 0.0;
  rsi_ = 0;
  rsiGainTotal_ = 0.0;
  rsiLossTotal_ = 0.0;
  currentRatios_[0] = 0;
}

void MeanReversionInput::getInputAtPeriod(int period) {
  period_ = period;
  currPrice_ = data_[period]->price_.price();
  movingAverageTotal_ += currPrice_;
  if (period >= MOVING_AVERAGE_PERIOD) {
    movingAverageTotal_ -= data_[period - MOVING_AVERAGE_PERIOD]->price_.price();
  }
  movingAverage_ = movingAverageTotal_ / (double) MOVING_AVERAGE_PERIOD;

  if (period > 0) {
    double prevPrice = data_[period - 1]->price_.price();
    double currRsi = (currPrice_ - prevPrice) * 100.0 / prevPrice;

    if (currRsi >= 0.0) {
      rsiGainTotal_ += currRsi;
    } else {
      rsiLossTotal_ += fabs(currRsi);
    }

    rsiWindow_.push_back(currRsi);
  }

  if (period >= RSI_PERIOD + 1) {
    double frontRsi = rsiWindow_.front();
    if (frontRsi >= 0.0) {
      rsiGainTotal_ -= frontRsi;
    } else {
      rsiLossTotal_ -= fabs(frontRsi);
    }
  }

  rsi_ = 100.0 - (100.0 / (1.0 + (rsiGainTotal_ / rsiLossTotal_)));
}

MeanReversion::MeanReversion() {
  buyPeriod_ = -1;
}

bool MeanReversion::isBuySignal(std::shared_ptr<MeanReversionInput> input) {
  return (input->currPrice_ >= input->movingAverage_) && (input->rsi_ >= rsiBuyThreshold_);
}

bool MeanReversion::isSellSignal(std::shared_ptr<MeanReversionInput> input) {
  int sellPeriod = buyPeriod_ + sellPeriodThreshold_;
  return (input->rsi_ >= rsiSellThreshold_) || (input->period_ > sellPeriodThreshold_);
}

int MeanReversion::operator()(int assetNum, std::shared_ptr<StrategyInput> input) {
  if (input->period_ < MOVING_AVERAGE_PERIOD - 1) {
    return 0;
  }

  std::shared_ptr<MeanReversionInput> newInput =
      std::reinterpret_pointer_cast<MeanReversionInput>(input);

  // if the portfolio currently does not hold the asset
  if (buyPeriod_ < 0) {
    if (isBuySignal(newInput)) {
      return 100;
    }
  } else {
    if (isSellSignal(newInput)) {
      return 0;
    }
  }

  return newInput->currentRatios_[0];
}
