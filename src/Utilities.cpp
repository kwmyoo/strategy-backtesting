//
// Created by Kun Woo Yoo on 2023/02/11.
//

#include <iostream>
#include "Utilities.h"

void split(std::string str, std::string splitBy, std::vector<std::string>& tokens) {
  tokens.push_back(str);
  size_t splitAt;
  size_t splitLen = splitBy.size();
  std::string frag;

  while (true) {
    frag = tokens.back();
    splitAt = frag.find(splitBy);

    if (splitAt == std::string::npos) {
      break;
    }

    tokens.back() = frag.substr(0, splitAt);
    tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
  }
}

Time::Time(const std::string& date_string) {
  tm tm = {};
  std::stringstream ss(date_string);
  ss >> std::get_time(&tm, "%b %d, %Y");
  time_ = mktime(&tm);
}

Time& Time::operator=(Time&& other) {
  time_ = std::move(other.time_);
  return *this;
}

Price::Price(const std::string& price_string) {
  for (const char& c: price_string) {
    if (c == ',') continue;
    price_ *= 10;
    price_ += (c - '0');
  }
}

Price& Price::operator=(Price&& other) {
  price_ = other.price_;
  return *this;
}