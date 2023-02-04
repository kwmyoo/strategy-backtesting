//
// Created by Kun Woo Yoo on 2023/01/30.
//

#ifndef STRATEGY_BACKTESTING_INVESTING_COM_H
#define STRATEGY_BACKTESTING_INVESTING_COM_H

#import <iomanip>
#import <sstream>
#import <string>
#import <tuple>
#import <time.h>
#import <ctime>

#import "data/provider/csv_template.h"

class Time {
 public:
  Time() {}

  Time(const std::string& date_string) {
    std::tm tm = {};
    std::stringstream ss(date_string);
    ss >> std::get_time(&tm, "%b %d, %Y");
    time_ = std::mktime(&tm);
  }

  Time(Time&& other) : time_(other.time_) {}

  Time& operator=(Time&& other) {
    time_ = std::move(other.time_);
    return *this;
  }

  std::time_t time() const { return time_; }

 private:
  std::time_t time_;
};

class Price {
 public:
  Price() {}

  Price(const std::string& price_string) {
    for (const char& c: price_string) {
      price_ *= 10;
      price_ += (c - '0');
    }
  }

  Price(Price&& otherPrice) : price_(otherPrice.price_) {}

  Price& operator=(Price&& other) {
    price_ = other.price_;
    return *this;
  }

  int price() { return price_; }

 private:
  int price_;
};

class InvestingComPeriod : public Period {
 public:
  InvestingComPeriod(Time&& time, Price&& price) : time_(std::move(time)), price_(std::move(price)) {}

 private:
  Time time_;
  Price price_;
};

#endif //STRATEGY_BACKTESTING_INVESTING_COM_H
