//
// Created by Kun Woo Yoo on 2023/02/02.
//

#ifndef STRATEGY_BACKTESTING_UTILITIES_H
#define STRATEGY_BACKTESTING_UTILITIES_H

#include <ctime>
#include <time.h>
#include <tuple>
#include <sstream>
#include <iomanip>
#include <deque>
#include <memory>
#include <string>

#include "Period.h"
#include "Strategy/Strategy.h"

enum class FileType {
  CSV
};

enum class TimeOrientation {
  NORMAL, // small to big
  INVERSED // big to small
};

class Time {
 public:
  Time() {}

  Time(const std::string& date_string) {
    tm tm = {};
    std::stringstream ss(date_string);
    ss >> std::get_time(&tm, "%b %d, %Y");
    time_ = mktime(&tm);
  }

  Time(Time&& other) : time_(other.time_) {}

  Time& operator=(Time&& other) {
    time_ = std::move(other.time_);
    return *this;
  }

  time_t time() const { return time_; }

  std::string ToString() {
    return std::to_string(time_);
  }

 private:
  time_t time_;
};

class Price {
 public:
  Price() {}

  Price(const std::string& price_string) : price_(0) {
    for (const char& c: price_string) {
      if (c == ',') continue;
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

  std::string ToString() {
    return std::to_string(price_);
  }

 private:
  int price_;
};

typedef std::deque<std::unique_ptr<Period>> HistoricalData;

typedef std::unique_ptr<Strategy> StrategyFn;

#endif //STRATEGY_BACKTESTING_UTILITIES_H
