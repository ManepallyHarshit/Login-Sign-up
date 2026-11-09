# 🔐 Password Auth System + Rock-Paper-Scissors Game

A secure, modular C++ console application combining user authentication, password strength validation, and an interactive Rock-Paper-Scissors game with persistent score tracking. 

---

## 🚀 What It Does

* **User Registration** — Create a secure account with custom or auto-generated passwords.
* **Authentication Login** — Sign in with credential verification.
* **Interactive Gameplay** — Play Rock-Paper-Scissors against a smart computer opponent.
* **Score Persistence** — Wins, losses, and draws are tracked and saved automatically per user.

---

## 🛠️ Quick Start

### 1. Build
Compile the project using any C++17 compliant compiler:
```bash
g++ -std=c++17 main.cpp auth.cpp game.cpp utils.cpp -o main
```

### 2. Run
```bash
./main
```

---

## 📖 How to Use

1. **Register** (`Option 1`)
   * Enter your desired username.
   * Choose to type your own password or have the system generate a strong one.
   * *Note: Passwords must be at least 7 characters long.*
2. **Login** (`Option 2`)
   * Enter your registered username and password.
3. **Play Game** (Unlocked after successful login)
   * Type **`r`** for Rock, **`p`** for Paper, or **`s`** for Scissors.
   * View the round outcome instantly.
   * Scores update and save automatically after every round.
4. **Exit** (`Option 3`)

---

## 🔒 Password Strength Validator

The application analyzes passwords based on character variety (lowercase, uppercase, numbers, and symbols):

| Strength | Criteria / Meaning | Status |
| :--- | :--- | :--- |
| **WEAK** | Only one character type | ❌ **Rejected** |
| **GOOD** | Two character types (e.g., letters + numbers) | ✅ Accepted |
| **EXCELLENT** | Three character types | ✅ Accepted |
| **EXCELLENT+** | All four: lowercase, UPPERCASE, numbers, symbols (`!@#`) | ✅ Accepted |

---

## 📂 Project Structure & Files

| File | Purpose |
| :--- | :--- |
| `main.cpp` | Main control flow & application entry point |
| `auth.h` / `auth.cpp` | User registration, login verification, and file handling |
| `game.h` / `game.cpp` | Rock-Paper-Scissors logic & score persistence |
| `utils.h` / `utils.cpp` | Password strength checker & secure password generator |

### Generated Data Files
Upon running, the app automatically manages local flat-file storage:
* `userdata.txt` — Stores account information (usernames & hashed/plain credentials).
* `<username>-score.txt` — Stores individual player game statistics (wins/losses/draws).

---

## ⚙️ Code Architecture & Modern C++ Features

* **Modular Design** — Clean header (`.h`) and implementation (`.cpp`) separation.
* **Include Guards** — Protected across all header files using `#ifndef`/`#define`/`#endif`.
* **Namespaces** — Encapsulated utility logic inside the `Utils` namespace.
* **Modern Randomness** — Uses `<random>` (`std::mt19937` and `std::uniform_int_distribution`) instead of legacy `rand()`.
* **Resource Safety (RAII)** — Leverages `std::string`, `std::fstream`, and `std::vector` for safe memory management.
* **Const-Correctness** — Utilizes `const` methods and references for code safety.
* **Clean Dependencies** — Uses forward declarations (e.g., `struct Score;` in `game.h`) to minimize coupling.
* **C++17 Standards** — Built with modern C++ features.

---

## 💻 Requirements

* **Compiler:** Any C++17 compatible compiler (`g++`, `clang++`, `MSVC`)
* **Dependencies:** Zero external libraries required.

---# Login-Sign-up
