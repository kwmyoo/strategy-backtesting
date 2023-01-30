//
// Created by Kun Woo Yoo on 2023/01/30.
//

#ifndef STRATEGY_BACKTESTING_INVESTING_COM_H
#define STRATEGY_BACKTESTING_INVESTING_COM_H

#import <sstream>
#import <string>
#import <tuple>
#import <time.h>

class Date {
  Date(const std::string& dateString) {
    std::tm tm = {};
    std::stringstream ss(dateString);
    ss >> std::get_time(&tm, "%b %d, %Y");
  }
};

class Price {
  Price(const std::string& priceString) {

  }
};

class InvestingComTemplate {
 public:
  const std::string headers[7] = {"Date", "Price", "Open", "High", "Low", "Vol.", "Change %"};

  InvestingComTemplate() {}

  std::tuple row<Date, Price, std::string, std::string, std::string, std::string, std::string>;
};

#endif //STRATEGY_BACKTESTING_INVESTING_COM_H
