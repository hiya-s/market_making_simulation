import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("data/output.csv")

plt.figure(figsize=(12,5))
plt.plot(df["t"], df["mid"], label="Mid")
plt.plot(df["t"], df["bid"], label="Quoted Bid")
plt.plot(df["t"], df["ask"], label="Quoted Ask")
plt.title("Bid/Ask/Mid Over Time")
plt.xlabel("t")
plt.ylabel("price")
plt.legend()
plt.grid(True)
plt.show()

plt.figure(figsize=(12,4))
plt.plot(df["t"], df["inventory"], label="Inventory")
plt.title("Inventory Over Time")
plt.xlabel("t")
plt.ylabel("units")
plt.legend()
plt.grid(True)
plt.show()

plt.figure(figsize=(12,4))
plt.plot(df["t"], df["pnl"], label="PnL (Mark-to-Market)")
plt.title("PnL Over Time")
plt.xlabel("t")
plt.ylabel("PnL")
plt.legend()
plt.grid(True)
plt.show()
