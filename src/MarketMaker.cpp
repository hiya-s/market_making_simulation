#include "MarketMaker.h"
#include <algorithm>
#include <cmath>

Quote MarketMaker::quote(const Market& m) const {
    // Inventory skew: if inventory positive, discourage more buying => lower bid, lower ask
    const double skew = inventory_k * inventory;

    const double mid = m.mid();
    Quote q;
    q.bid = mid - spread / 2.0 - skew;
    q.ask = mid + spread / 2.0 - skew;

    if (q.ask <= q.bid) q.ask = q.bid + 0.01;
    return q;
}

void MarketMaker::on_fill(bool buy, double px) {
    if (buy) {         // we bought at bid
        inventory += 1.0;
        cash -= px;
    } else {           // we sold at ask
        inventory -= 1.0;
        cash += px;
    }
}

void MarketMaker::update_spread() {
    // widen spread as inventory magnitude increases
    const double inv_abs = std::abs(inventory);
    spread = base_spread * (1.0 + spread_k * inv_abs);

    // optional: hard penalty when beyond risk_limit
    if (inv_abs > risk_limit) {
        spread *= 1.25;
    }

    spread = std::max(spread, 0.05); // never too tight
}

double MarketMaker::pnl_mark_to_market(double mid) const {
    return cash + inventory * mid;
}
