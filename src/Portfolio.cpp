//
// Created by Kun Woo Yoo on 2023/02/06.
//
#include <iostream>
#include <math.h>

#include "Portfolio.h"

double Asset::getAllocatedMoney(double total, int ratio) const {
  return floor((total * ratio) / 100.0);
}

double Asset::buy(double allocated, double price) {
  quantity_ = floor(allocated / price);
  return quantity_ * price;
}

double Asset::sell() {
  double tmp = quantity_;
  quantity_ = 0;
  return tmp;
}

void Portfolio::addAsset(Asset&& portfolioAsset) {
  assets_.emplace_back(std::move(portfolioAsset));
}