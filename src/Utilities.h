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

#define CSV_FORMAT_DEFAULT_TEMPLATE unsigned column_count, \
class trim_policy = io::trim_chars<' ', '\t'>, \
class quote_policy = io::no_quote_escape<','>, \
class overflow_policy = io::throw_on_overflow, \
class comment_policy = io::no_comment

#define CSV_FORMAT_TEMPLATE unsigned column_count, \
class trim_policy, \
class quote_policy, \
class overflow_policy, \
class comment_policy

#define CSV_FORMAT column_count, \
trim_policy, \
quote_policy, \
overflow_policy, \
comment_policy

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
  Time time_;

  Price price_;

  Period(Time&& time, Price&& price) {
    time_ = std::move(time);
    price_ = std::move(price);
  }

  const Time& time() const { return time_; }

  const Price& price() const { return price_; }

  std::string toString() {
    return "Price: " + price_.toString() + ", Time: " + time_.toString();
  }
};

#endif //STRATEGY_BACKTESTING_UTILITIES_H
