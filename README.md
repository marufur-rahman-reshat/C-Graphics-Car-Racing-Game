# 🏎️ Car Racing Game using OpenGL/GLUT (C++)

<p align="center">
  <img src="screenshots/gameplay.png" width="45%"/>
  <img src="screenshots/start_screen.png" width="45%"/>
</p>

## 📖 About
A top-down 2D car racing game built with **C++ and OpenGL/GLUT** as a Computer Graphics project. The player controls a blue car, overtakes enemy cars, collects coins, and tries to survive as long as possible while the speed increases over time.

---

## 🎮 Gameplay

- **3 lanes** to drive in
- **3 enemy cars** coming from the top
- **3 coins** to collect for bonus points
- **Speed increases** every 10 seconds
- **3 lives** — game ends when all lives are lost
- **Rank system** based on final score

---

## 🏆 Scoring

| Action | Points |
|--------|--------|
| Collect a coin | +20 |
| Overtake an enemy car | +10 |
| Enemy exits screen | +5 |
| Survive 10 seconds | +5 bonus |

## 🥇 Ranks

| Score | Rank |
|-------|------|
| 500+ | LEGEND! |
| 300+ | PRO! |
| 100+ | GOOD! |
| 0–99 | BEGINNER |

---

## 🎯 Controls

| Key | Action |
|-----|--------|
| `ENTER` | Start game |
| `←` Left Arrow | Move car left |
| `→` Right Arrow | Move car right |
| `↑` Up Arrow | Speed up |
| `↓` Down Arrow | Slow down |
| `R` | Restart game |
| `ESC` | Quit |

---

## 🛠️ Built With

| Tool | Details |
|------|---------|
| Language | C++ |
| Graphics | OpenGL / GLUT |
| IDE | CodeBlocks 20.03 |
| OS | Windows |

---

## ⚙️ How to Run

### Requirements
- Windows OS
- CodeBlocks 20.03
- GLUT library installed

### Steps

**1. Clone the repository:**
```bash
```

**2. Open CodeBlocks**

**3. Create a new Empty Project**

**4. Add the source file:**
- Right click **Sources** → **Add files**
- Select `src/main.cpp`

**5. Link GLUT libraries:**
- Go to **Project → Build Options → Linker Settings**
- Add these under **Other linker options:**
```
-lglut32
-lglu32
-lopengl32
```

**6. Build and Run:**
- Press `F9` or click **Build and Run**

---

## 📂 Project Structure

```
Car-Racing-Game-OpenGL/
│
├── src/
│   └── main.cpp          # Full game source code
│
├── screenshots/
│   ├── start_screen.png  # Start screen screenshot
│   ├── gameplay.png      # Gameplay screenshot
│   └── game_over.png     # Game over screenshot
│
├── docs/
│   └── controls.md       # Detailed controls guide
│
├── .gitignore            # Git ignore file
└── README.md             # This file
```

---

## 🚀 Features

- ✅ Top-down view car racing
- ✅ 3 lane road system
- ✅ Animated scrolling road with lane dividers
- ✅ 3 randomly colored enemy cars
- ✅ Coin collection system
- ✅ Score and lives HUD
- ✅ Difficulty increases over time
- ✅ Start screen with controls
- ✅ Game over screen with rank
- ✅ Speed control by player

---

## 📚 Course Info

- **Course:** Computer Graphics Lab
- **Topic:** 2D Game Development using OpenGL
- **Language:** C++

---

## 👨‍💻 Author

**RESHAT, MARUFUR RAHMAN**
Student
Computer Science Engineering
American International University-Bangladesh.(AIUB)

---

## 📄 License

This project is for **academic purposes** only.
