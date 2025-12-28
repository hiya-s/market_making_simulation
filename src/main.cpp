#include <iostream>
#include <string>
#include "Simulator.h"

int main(int argc, char** argv) {
    SimParams p;
    unsigned seed = 42;
    std::string out = "data/output.csv";

    if (argc >= 2) p.steps = std::stoi(argv[1]);
    if (argc >= 3) seed = static_cast<unsigned>(std::stoul(argv[2]));
    if (argc >= 4) out = argv[3];

    Simulator sim(seed, p);
    sim.run(out);

    std::cout << "✅ Simulation complete. CSV written to: " << out << "\n";
    std::cout << "Run Python viz: python viz/plot_timeseries.py\n";
    return 0;
}
