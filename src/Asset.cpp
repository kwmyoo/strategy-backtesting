//
// Created by Kun Woo Yoo on 2023/02/04.
//

#include "Asset.h"
#include "Utilities.h"

Asset::Asset(std::string&& name, HistoricalData&& historical_data)
    : name_(std::move(name)),
      historical_data_(std::move(historical_data)) {
  quantity = 0;
}

int Asset::Buy(int total) {

}