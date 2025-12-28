#pragma once

struct Market {
    double best_bid;
    double best_ask;

    Market(double bid = 99.5, double ask = 100.5) : best_bid(bid), best_ask(ask) {}

    double mid() const { return (best_bid + best_ask) / 2.0; }
    double spread() const { return best_ask - best_bid; }

    void clamp() {
        if (best_ask <= best_bid) best_ask = best_bid + 0.01; // ensure valid book
    }
};
