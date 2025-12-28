# Market-Making Simulator (C++ + Python + SFML)

A lightweight market-making simulation that demonstrates:
- quoting bid/ask around a mid-price
- dynamic spread management
- inventory & risk control
- CSV export for analysis
- visualization (Python plots + optional SFML real-time viewer)

## Why this project
Market-making requires balancing profitability (capturing spread) with risk (inventory exposure).
This simulator models a simple environment and shows how quoting logic adapts to inventory.

## Features
- **C++17 simulator** with modular classes (Market, MarketMaker, Simulator)
- **Inventory skew**: quotes shift to reduce undesirable exposure
- **Dynamic spread** widens as inventory magnitude increases
- **Mark-to-market PnL**
- **Python plotting**
- **Monte Carlo runner** to observe PnL distribution and inventory risk
- **Optional SFML viewer** for a real-time demo

## Build & Run (C++)
```bash
mkdir -p build
cmake -S . -B build
cmake --build build -j

./build/sim 1000 42 data/output.csv
