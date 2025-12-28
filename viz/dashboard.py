import pandas as pd
import numpy as np
import streamlit as st
import matplotlib.pyplot as plt

st.set_page_config(layout="wide")
st.title("Market-Making Simulator Dashboard")

df = pd.read_csv("data/output.csv")

# -----------------------------
# Time Series Plots
# -----------------------------
st.subheader("Price Dynamics")

fig, ax = plt.subplots(figsize=(10,4))
ax.plot(df["t"], df["mid"], label="Mid")
ax.plot(df["t"], df["bid"], label="Bid")
ax.plot(df["t"], df["ask"], label="Ask")
ax.legend()
ax.set_xlabel("Time")
ax.set_ylabel("Price")
st.pyplot(fig)

# -----------------------------
# Inventory
# -----------------------------
st.subheader("Inventory Over Time")

fig, ax = plt.subplots(figsize=(10,3))
ax.plot(df["t"], df["inventory"])
ax.set_xlabel("Time")
ax.set_ylabel("Inventory")
st.pyplot(fig)

# -----------------------------
# PnL
# -----------------------------
st.subheader("PnL Over Time")

fig, ax = plt.subplots(figsize=(10,3))
ax.plot(df["t"], df["pnl"])
ax.set_xlabel("Time")
ax.set_ylabel("PnL")
st.pyplot(fig)

# -----------------------------
# Monte Carlo
# -----------------------------
st.subheader("Monte Carlo Risk Analysis")

pnl_diff = np.diff(df["pnl"].values)

N = st.slider("Monte Carlo runs", 100, 2000, 500)

final_pnls = []
for _ in range(N):
    sampled = np.random.choice(pnl_diff, size=500, replace=True)
    final_pnls.append(sampled.sum())

fig, ax = plt.subplots(figsize=(8,4))
ax.hist(final_pnls, bins=40)
ax.set_xlabel("Final PnL")
ax.set_ylabel("Frequency")
st.pyplot(fig)
