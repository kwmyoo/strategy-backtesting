//
// Created by Kun Woo Yoo on 2023/02/04.
//

#ifndef STRATEGY_BACKTESTING_ASSET_H
#define STRATEGY_BACKTESTING_ASSET_H

#include "Utilities.h"

class Asset {
 public:
  std::string name_;

  int quantity_;

  int price_;

  Asset(std::string&& name) : name_(std::move(name)) {
    quantity_ = 0;
  }

  Asset(Asset&& other) : name_(std::move(other.name_)), quantity_(other.quantity_), price_(other.price_) {}

  int Buy(int total);

  int Sell();
};

#endif //STRATEGY_BACKTESTING_ASSET_H
