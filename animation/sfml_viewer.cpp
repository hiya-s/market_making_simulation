#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Row {
    float bid, ask, mid, inv, pnl;
};

static std::vector<Row> load_csv(const std::string& path) {
    std::ifstream f(path);
    std::string line;
    std::vector<Row> rows;

    std::getline(f, line); // header
    while (std::getline(f, line)) {
        std::stringstream ss(line);
        std::string v;

        // t,bid,ask,mid,book_bid,book_ask,inventory,cash,pnl,spread
        std::getline(ss, v, ','); // t
        Row r{};
        std::getline(ss, v, ','); r.bid = std::stof(v);
        std::getline(ss, v, ','); r.ask = std::stof(v);
        std::getline(ss, v, ','); r.mid = std::stof(v);
        std::getline(ss, v, ','); // book_bid
        std::getline(ss, v, ','); // book_ask
        std::getline(ss, v, ','); r.inv = std::stof(v);
        std::getline(ss, v, ','); // cash
        std::getline(ss, v, ','); r.pnl = std::stof(v);
        rows.push_back(r);
    }
    return rows;
}

int main() {
    auto rows = load_csv("data/output.csv");
    if (rows.empty()) return 1;

    const int W = 1000, H = 600;
    sf::RenderWindow window(sf::VideoMode(W, H), "Market-Making Viewer (SFML)");
    window.setFramerateLimit(60);

    float minP = rows[0].bid, maxP = rows[0].ask;
    for (auto& r : rows) { minP = std::min(minP, r.bid); maxP = std::max(maxP, r.ask); }
    const float pad = 1.0f;
    minP -= pad; maxP += pad;

    auto ymap = [&](float p) {
        float u = (p - minP) / (maxP - minP);
        return (1.0f - u) * (H * 0.65f) + 40.0f; // top chart area
    };

    size_t i = 0;
    const int visible = 350;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
        }

        window.clear();

        // draw axes area
        sf::RectangleShape chart(sf::Vector2f((float)W - 80, H * 0.65f));
        chart.setPosition(40, 20);
        chart.setFillColor(sf::Color(20, 20, 20));
        chart.setOutlineThickness(1);
        chart.setOutlineColor(sf::Color(80, 80, 80));
        window.draw(chart);

        // draw lines for bid/ask/mid over visible range
        size_t start = (i > (size_t)visible) ? i - visible : 0;
        size_t end = std::min(i, rows.size() - 1);

        auto draw_series = [&](auto getP, sf::Color c) {
            sf::VertexArray va(sf::LineStrip);
            for (size_t k = start; k <= end; ++k) {
                float x = 40.0f + (float)(k - start) * ((W - 80.0f) / (float)visible);
                float y = ymap(getP(rows[k]));
                va.append(sf::Vertex(sf::Vector2f(x, y), c));
            }
            window.draw(va);
        };

        draw_series([](const Row& r){ return r.bid; }, sf::Color::Green);
        draw_series([](const Row& r){ return r.ask; }, sf::Color::Red);
        draw_series([](const Row& r){ return r.mid; }, sf::Color::White);

        // simple inventory bar at bottom
        float inv = rows[end].inv;
        sf::RectangleShape invBar(sf::Vector2f(std::min(std::abs(inv)*10.0f, (float)W-120), 18));
        invBar.setPosition(60, H - 60);
        invBar.setFillColor(inv >= 0 ? sf::Color::Cyan : sf::Color(255, 200, 0));
        window.draw(invBar);

        window.display();

        i = std::min(i + 1, rows.size() - 1);
    }

    return 0;
}
