# FSS-3.4 (Flight Schedule System)

**FSS-3.4** is a terminal-based Flight Planning & Speed Estimation System written in C++. It simulates key preflight calculations for commercial aircraft including **V2 speed**, **approach speed (VAPP)**, **stall speed**, and full **pre-scheduled flight planning** with altitude, distance, and speed profiles.

---

## ✈️ Features

- **V2 Speed Calculation**: Determines the takeoff safety speed based on aircraft type, mass, flap setting, pressure, and temperature.
- **VAPP Speed Calculation**: Computes the final approach speed.
- **Stall Speed Calculation**: Calculates minimum flying speed before stall, considering altitude and weight.
- **Pre-Schedule Planning**: Create a full flight profile with:
  - Departure & arrival altitudes
  - Cruising and descent speeds
  - Vertical speeds
  - Distances and estimated time
- **Interactive Terminal UI**: Menu navigation using `W`, `S`, and `Enter`.
- **Unit Switching**: Supports both metric and American units (kg/lb, hPa/inHg).
- **Aircraft Support**:
  - Boeing 737-800  
  - Airbus A330-300  
  - Boeing 787-9

---

## 🛠 How to Use

### Compile
Make sure you have a C++11 compatible compiler. You also need to include `vertical.h`, which contains the aerodynamic formulas (`v2_speed`, `stall_speed`, `eqx`, `eqh`, etc.).

```bash
g++ main.cpp -o fss
