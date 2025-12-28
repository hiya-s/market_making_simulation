#pragma once
#include "Market.h"

struct Quote {
    double bid;
    double ask;
};

class MarketMaker {
public:
    double inventory = 0.0;
    double cash = 0.0;

    double base_spread = 1.0;
    double spread = 1.0;

    double risk_limit = 10.0;
    double inventory_k = 0.05;     // how strongly inventory skews quotes
    double spread_k = 0.02;        // how strongly spread widens with inventory

    Quote quote(const Market& m) const;
    void on_fill(bool buy, double px); // buy=true means we bought (inventory++)
    void update_spread();
    double pnl_mark_to_market(double mid) const;
};
