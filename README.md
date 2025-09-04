# 🚦 Rush Hour 2D

**Rush Hour 2D** is a fast-paced traffic management and delivery simulation game written in **C++ with OpenGL/GLUT**.
It blends **strategy, chaos, and reflexes** into a colorful arcade-style challenge.

You’re either the **master of traffic lights** or the **delivery driver racing against time** — but in both cases, your choices decide if the city thrives or collapses into chaos.

---

## 🌟 Highlights

* 🎮 **Two Distinct Game Modes**

  * **Traffic Controller** → Manage roads, prevent crashes, and keep the city safe.
  * **Delivery Driver** → Pick up jobs, conserve fuel, dodge traffic, and deliver packages.

* 🔄 **Dynamic Gameplay**

  * Randomized jobs and destinations.
  * Cars spawn at unpredictable locations.
  * No two playthroughs feel the same.

* 🛢️ **Petrol System**

  * Fuel is limited! Use it wisely, or your run ends.

* 🏆 **Leaderboard**

  * Persistent scores saved in `leaderboard.txt`.
  * Compete with yourself and friends for the highest score.

* 🔊 **Sound Support**

  * Powered by **mpg123** for background music and sound effects.

* 🎨 **Graphics**

  * Clean 2D rendering with OpenGL & GLUT.
  * Bright and engaging visuals for every object.

---

## 🖥️ Demo Flow

1. **Startup Screen** → Enter your name → Select role:

   * Press **`d`** for Delivery Driver
   * Press **`t`** for Traffic Controller

2. **Gameplay** →

   * Control your vehicle with **`WASD`**
   * Manage jobs/deliveries or control cars
   * Watch your petrol and score

3. **Endgame** →

   * Your score is saved
   * Leaderboard updated automatically

---

## 🎮 Controls

| Key             | Action                           |
| --------------- | -------------------------------- |
| `w` `a` `s` `d` | Move player vehicle              |
| `space`         | Deliver job (Delivery Mode)      |
| `+` `-`         | Adjust petrol                    |
| `o`             | Quit game                        |
| `p`             | Resume game                      |
| `Escape`        | Return to menu                   |
| `d`             | Choose Delivery Driver (Menu)    |
| `t`             | Choose Traffic Controller (Menu) |

---

## 📂 File Structure

```
RushHour2D/
│── main.cpp              # Main game loop & logic
│── util.h                # Utility functions for graphics (shapes, drawing)
│── leaderboard.txt        # Persistent high scores
│── assets/               # Sounds, images, textures (if any)
│── build/                # Compiled output
```

---

## 🛠️ Installation

### Dependencies

* **C++ Compiler** (g++, clang++, or MSVC)
* **OpenGL** & **GLUT**
* **mpg123** (for audio)

### Build & Run

```bash
# Clone the repository
git clone https://github.com/your-username/RushHour2D.git
cd RushHour2D

# Compile
g++ main.cpp -lGL -lGLU -lglut -lmpg123 -o RushHour2D

# Run
./RushHour2D
```

---

## 🏆 Leaderboard

Scores are automatically stored in `leaderboard.txt`.

**Format:**

```
Player: Usaid  Score: 1200
Player: Ahmed  Score: 950
Player: Saram  Score: 870
```

The system sorts scores, so only the best remain at the top.

---

## 📸 Screenshots & Preview

*(Add game screenshots or GIFs here — menu, gameplay, leaderboard, etc.)*

---

## 🚀 Roadmap / Future Ideas

* Smarter AI traffic behavior
* Power-ups (extra fuel, time boosts)
* More diverse maps
* Weather effects (rain/night mode)
* Multiplayer (LAN or online)

---

## 🤝 Contributing

Want to improve **Rush Hour 2D**?

* Fork the repo
* Create a feature branch
* Submit a Pull Request

---

## 📜 License

This project is open-source and licensed under the **MIT License**.

---

## 💡 Behind the Scenes

This game was built as a **university-level project** to explore:

* Core **C++ programming** concepts (operators, file handling, classes)
* **Graphics programming** using OpenGL/GLUT
* Managing **state machines** for menus/gameplay
* Designing with **object-oriented thinking** (vehicles, jobs, players)
