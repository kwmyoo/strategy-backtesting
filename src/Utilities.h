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
#include <memory>
#include <string>
#include <vector>

void split(std::string str, std::string splitBy, std::vector<std::string>& tokens);

enum class FileType {
  CSV
};

enum class TimeOrientation {
  NORMAL, // small to big
  INVERSED // big to small
};

class Time {
 public:
  Time() = default;

  Time(const std::string& date_string);

  Time(Time&& other) : time_(other.time_) {}

  Time& operator=(Time&& other);

  time_t time() const { return time_; }

  std::string toString() {
    return std::to_string(time_);
  }

 private:
  time_t time_;
};

class Price {
 public:
  Price() {}

  Price(const std::string& price_string);

  Price(Price&& otherPrice) : price_(otherPrice.price_) {}

  Price& operator=(Price&& other);

  int price() { return price_; }

  std::string toString() {
    return std::to_string(price_);
  }

 private:
  int price_;
};

class Period {
 public:
  virtual ~Period() {}

  virtual std::string toString() = 0;

  Time time_;

  Price price_;
};

#endif //STRATEGY_BACKTESTING_UTILITIES_H
