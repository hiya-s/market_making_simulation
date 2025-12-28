#pragma once
#include <random>
#include <string>
#include "Market.h"
#include "MarketMaker.h"

struct SimParams {
    int steps = 1000;
    double price_vol = 0.15;       // random walk step size
    double fill_prob = 0.55;       // probability an order hits one side each step
};

class Simulator {
public:
    Simulator(unsigned seed, SimParams p);

    void run(const std::string& csv_path);

private:
    std::mt19937 rng;
    SimParams params;

    std::uniform_real_distribution<double> U01;
    std::normal_distribution<double> N01;
};
