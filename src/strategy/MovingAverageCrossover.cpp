//
// Created by Kun Woo Yoo on 2023/08/22.
//

#include <iostream>

#include "MovingAverageCrossover.h"

MovingAverageCrossoverInput::MovingAverageCrossoverInput(Backtest* backtest)
    : StrategyInput(backtest->ratios_),
      data_(backtest->historicalData_.data_[0]) {
  shortTermTotal_ = 0.0;
  shortTermMovingAverage_ = 0.0;
  longTermTotal_ = 0.0;
  longTermMovingAverage_ = 0.0;
  currentRatios_[0] = 100;
}

void MovingAverageCrossoverInput::getInputAtPeriodWithRatio(int period) {
  period_ = period;
  ratio_ = currentRatios_[0];
  double currentPrice = data_[period]->price_.price();
  shortTermTotal_ += currentPrice;
  longTermTotal_ += currentPrice;

  if (period >= LONG_TERM_MA_PERIOD) {
    longTermTotal_ -= data_[period - LONG_TERM_MA_PERIOD]->price_.price();
  }
  if (period >= SHORT_TERM_MA_PERIOD) {
    shortTermTotal_ -= data_[period - SHORT_TERM_MA_PERIOD]->price_.price();
  }

  shortTermMovingAverage_ = shortTermTotal_ / (double) SHORT_TERM_MA_PERIOD;
  longTermMovingAverage_ = longTermTotal_ / (double) LONG_TERM_MA_PERIOD;
}

MovingAverageCrossover::MovingAverageCrossover()
    : status_(MovingAverageStatus::INITIAL) {}


MovingAverageStatus
MovingAverageCrossover::getCurrentStatus(double shortTermMovingAverage, double longTermMovingAverage) {
  if (shortTermMovingAverage < longTermMovingAverage) {
    return MovingAverageStatus::LONG_TERM_AVERAGE_HIGHER;
  } else if (shortTermMovingAverage == longTermMovingAverage) {
    return MovingAverageStatus::EQUAL;
  } else {
    return MovingAverageStatus::SHORT_TERM_AVERAGE_HIGHER;
  }
}

int MovingAverageCrossover::operator()(int assetNum, std::shared_ptr<StrategyInput> input) {
  if (input->period_ < LONG_TERM_MA_PERIOD - 1) {
    return 0;
  }
  std::shared_ptr<MovingAverageCrossoverInput> newInput =
      std::reinterpret_pointer_cast<MovingAverageCrossoverInput>(input);

  MovingAverageStatus newStatus = getCurrentStatus(
      newInput->shortTermMovingAverage_,
      newInput->longTermMovingAverage_
  );
  int result = newInput->ratio_;

  if (newStatus == MovingAverageStatus::SHORT_TERM_AVERAGE_HIGHER &&
      newStatus != status_) {
    result = 100;
  } else if (newStatus == MovingAverageStatus::LONG_TERM_AVERAGE_HIGHER &&
             newStatus != status_) {
    result = 0;
  }

  status_ = newStatus;
  return result;
}