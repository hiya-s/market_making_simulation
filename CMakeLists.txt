cmake_minimum_required(VERSION 3.16)
project(market_making_simulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(sim
    src/main.cpp
    src/MarketMaker.cpp
    src/Simulator.cpp
)

# SFML viewer is optional (build target only if SFML installed)
# add_executable(sfml_viewer
#     animation/sfml_viewer.cpp
# )
