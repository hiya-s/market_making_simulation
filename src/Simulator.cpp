#include "Simulator.h"
#include <fstream>
#include <iomanip>

Simulator::Simulator(unsigned seed, SimParams p)
    : rng(seed), params(p), U01(0.0, 1.0), N01(0.0, 1.0) {}

void Simulator::run(const std::string& csv_path) {
    Market m(99.5, 100.5);
    MarketMaker mm;

    std::ofstream out(csv_path);
    out << "t,bid,ask,mid,book_bid,book_ask,inventory,cash,pnl,spread\n";
    out << std::fixed << std::setprecision(6);

    for (int t = 0; t < params.steps; ++t) {
        // Random walk mid; keep book spread small and stable
        const double mid = m.mid() + params.price_vol * N01(rng);
        const double book_spread = 0.10; // market spread (environment)
        m.best_bid = mid - book_spread / 2.0;
        m.best_ask = mid + book_spread / 2.0;
        m.clamp();

        mm.update_spread();
        const Quote q = mm.quote(m);

        // simulate which side gets hit
        const double r = U01(rng);

        // if fill occurs, decide buy/sell hit based on inventory (slight reversion)
        if (r < params.fill_prob) {
            const double side = U01(rng);
            const bool hit_bid = (side < 0.5);

            if (hit_bid) mm.on_fill(true, q.bid);
            else mm.on_fill(false, q.ask);
        }

        const double pnl = mm.pnl_mark_to_market(m.mid());

        out << t << "," << q.bid << "," << q.ask << "," << m.mid() << ","
            << m.best_bid << "," << m.best_ask << ","
            << mm.inventory << "," << mm.cash << "," << pnl << "," << mm.spread
            << "\n";
    }
}
