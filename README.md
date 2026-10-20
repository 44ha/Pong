# 🏓 Vertical Neon Pong (C++ & SFML)

A modern, vertical-oriented Pong game written in **C++** using **SFML** with sleek neon aesthetics, dynamic lighting effects, and an intelligent AI opponent.

---

## 🎮 Game Features & Design

- **Vertical Court Layout**:
  - **Player 1 (Bottom Paddle)**: Cyan neon paddle controlled by arrow keys.
  - **AI Opponent (Top Paddle)**: Neon magenta/pink paddle with smooth tracking.
- **Dynamic Physics & Angle Steering**: Ball reflection angle adjusts based on where it hits the paddle, rewarding skilled edge shots.
- **Speed Escalation**: The ball accelerates with each successful rally hit up to a max speed limit.
- **Aesthetic Neon Glow**: Multi-pass aura rendering for ball and paddles.
- **Fail-safe Font System**: Loads a font from `assets/` if present, otherwise falls back to a system font, and finally to procedural 7-segment vector digits — all without crashing.

---

## 🕹️ Controls

| Key | Action |
|---|---|
| **← Left Arrow** | Move paddle left |
| **→ Right Arrow** | Move paddle right |
| **`P`** | Pause / Resume match |
| **`R`** | Restart match at any time |
| **`Escape`** | Exit game |

---

## 📁 Project Structure

```text
Pong/
├── assets/             # Optional: place a font here as font.ttf
├── src/
│   ├── Ball.h          # Ball state, speed, reflection physics & neon rendering
│   ├── Ball.cpp
│   ├── Paddle.h        # Paddle movement, boundaries, AI tracking & glow
│   ├── Paddle.cpp
│   ├── Game.h          # Game loop, states (Play/Pause/GameOver), HUD & event handling
│   ├── Game.cpp
│   └── main.cpp        # Application entry point
├── CMakeLists.txt      # Build configuration for CMake
└── README.md           # Documentation and build guide
```

---

## 🛠️ How to Build and Run

### Prerequisites

1. **CMake 3.16+**
2. **A C++17 compiler** (MSVC via Visual Studio, MinGW-w64 GCC, or Clang)
3. **SFML 2.5+**

---

### Option 1: Build with CMake & vcpkg (Recommended)

1. **Install SFML via vcpkg**:
   ```bash
   vcpkg install sfml:x64-windows
   ```

2. **Configure & Build**:
   ```bash
   cmake -B build -DCMAKE_TOOLCHAIN_FILE="[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake"
   cmake --build build --config Release
   ```

3. **Run**:
   ```bash
   ./build/Release/Pong.exe    # Windows (MSVC)
   ./build/Pong                # Linux / macOS
   ```

---

### Option 2: Build with MinGW (g++)

If you have MinGW with SFML installed:
```bash
g++ -std=c++17 src/*.cpp -o Pong -lsfml-graphics -lsfml-window -lsfml-system
./Pong
```

---

### Option 3: Visual Studio (Manual Setup)

1. Open Visual Studio → Create a new **C++ Empty Project**.
2. Add existing items from the `src/` folder (`main.cpp`, `Game.cpp`, `Game.h`, `Paddle.cpp`, `Paddle.h`, `Ball.cpp`, `Ball.h`).
3. In Project Properties:
   - **C/C++ → General → Additional Include Directories**: Add `SFML/include`.
   - **Linker → General → Additional Library Directories**: Add `SFML/lib`.
   - **Linker → Input → Additional Dependencies**: Add:
     - `sfml-graphics.lib`
     - `sfml-window.lib`
     - `sfml-system.lib`
4. Copy the SFML `.dll` files (`sfml-graphics-2.dll`, `sfml-window-2.dll`, `sfml-system-2.dll`) next to your generated `.exe`.
5. Press **F5** to compile and run!

---

## 🏆 Scoring Rules

- First player to reach **7 points** wins the match.
- Press **`R`** at the Game Over screen to instantly start a rematch.
