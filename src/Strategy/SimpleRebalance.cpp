//
// Created by Kun Woo Yoo on 2023/02/04.
//

#include "strategies/simple_rebalance.h"
#include "strategies/strategy.h"

SimpleRebalance::SimpleRebalance(long initial_amount) : Strategy(initial_amount) {}

void SimpleRebalance::Rebalance(int period) {
  std::vector <Asset>& assets = portfolio_.assets();
  std::vector<int>& ratio = portfolio_.ratio();
  for (int i = 0; i < assets.size(); i++) {

  }
}