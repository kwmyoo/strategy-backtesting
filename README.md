# strategy-backtesting

This is a simple framework to backtest different investment strategies.

Currently, it supports 4 strategies:

1. Simple rebalancing
2. Moving average crossover
3. Mean reversion
4. Pair trading

The detailed explanations of each algorithm is included in the code.

## How to use

This backtesting program utilizes command line options.

5 options are required:

- -s : strategy (currently supports rebalance, meanreversion, movingaveragecrossover, pairtrading)
- -f : date from
- -t : date to
- -b : initial balance
- -i : tickers

## Example

If I want to backtest pair trading strategy on ExxonMobil(XOM) and Shell(SHEL) from 2022-01-01 to 2022-12-31 with initial the
balance of $100,000,000, the command should be:

```
./strategy_backtesting -s pairtrading -f 2022-01-01 -t 2022-12-31 -b 100000000.0 -i XOM SHEL
```
