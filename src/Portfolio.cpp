//
// Created by Kun Woo Yoo on 2023/02/06.
//

#include "Portfolio.h"
#include "Asset.h"
#include "Utilities.h"
#include "Strategy/Strategy.h"

void Portfolio::Rebalance() {

}

void Portfolio::AddAsset(PortfolioAsset&& portfolio_asset) {
  portfolio_assets_.emplace_back(std::move(portfolio_asset));
}
