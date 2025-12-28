import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# ----------------------------
# CONFIG
# ----------------------------
CSV_PATH = "data/output.csv"
N_RUNS = 500
PATH_LENGTH = 500
SEED = 42

np.random.seed(SEED)

# ----------------------------
# LOAD DATA
# ----------------------------
df = pd.read_csv(CSV_PATH)

# Use PnL differences as return samples
pnl = df["pnl"].values
pnl_diff = np.diff(pnl)

# ----------------------------
# MONTE CARLO BOOTSTRAP
# ----------------------------
final_pnls = []
max_drawdowns = []

for _ in range(N_RUNS):
    sampled_returns = np.random.choice(
        pnl_diff, size=PATH_LENGTH, replace=True
    )

    path = np.cumsum(sampled_returns)
    final_pnls.append(path[-1])

    peak = np.maximum.accumulate(path)
    drawdown = peak - path
    max_drawdowns.append(drawdown.max())

final_pnls = np.array(final_pnls)
max_drawdowns = np.array(max_drawdowns)

# ----------------------------
# PLOTS
# ----------------------------
plt.figure(figsize=(10,5))
plt.hist(final_pnls, bins=40, edgecolor="black")
plt.title("Monte Carlo Final PnL Distribution")
plt.xlabel("Final PnL")
plt.ylabel("Frequency")
plt.grid(True)
plt.show()

plt.figure(figsize=(10,5))
plt.hist(max_drawdowns, bins=40, edgecolor="black", color="orange")
plt.title("Monte Carlo Max Drawdown Distribution")
plt.xlabel("Max Drawdown")
plt.ylabel("Frequency")
plt.grid(True)
plt.show()

# ----------------------------
# METRICS
# ----------------------------
print("Monte Carlo Summary")
print("-------------------")
print(f"Runs: {N_RUNS}")
print(f"Mean Final PnL: {final_pnls.mean():.2f}")
print(f"Std Final PnL: {final_pnls.std():.2f}")
print(f"Worst Drawdown (95%): {np.percentile(max_drawdowns, 95):.2f}")
