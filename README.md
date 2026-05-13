# 🐾 Virtual Pet System — OOP Final Project

A C++ console-based Virtual Pet simulation developed as a Final OOP Assignment.

## 📁 Project Structure

| File | Purpose |
|---|---|
| `main.cpp` | Entry point |
| `AsciiArt.h/.cpp` | ASCII art for pet moods |
| `Pet.h/.cpp` | Battery, Storage, PetState, VirtualPet classes |
| `Actions.h/.cpp` | Abstract Action class + Feed, Sleep, Play |
| `Notifications.h/.cpp` | Battery alert system |
| `FileManager.h/.cpp` | File I/O — save/load/delete pets |
| `Game.h/.cpp` | Main game loop and menu controller |
| `pets.txt` | Auto-generated data file (pet persistence) |

## 🧠 OOP Concepts Used

- **Inheritance** — `HardwareComponent` → `Battery`, `Storage`; `Action` → `Feed`, `Sleep`, `Play`; `NotificationBase` → `BatteryNotification`
- **Polymorphism** — virtual `perform()` and `display()` methods
- **Composition** — `VirtualPet` owns `Battery`, `Storage`, `PetState`
- **Encapsulation** — private members with public accessors
- **Static members** — `petCount`, `totalActionsPerformed`, `totalChargeCycles`
- **Friend functions/classes** — `revealSecrets()`, `Feed`
- **File Handling** — `FileManager` reads/writes `pets.txt`
- **Copy constructors & assignment operators** defined for all major classes

## ▶️ How to Compile & Run

```bash
g++ main.cpp AsciiArt.cpp Pet.cpp Actions.cpp Notifications.cpp FileManager.cpp Game.cpp -o VirtualPet
./VirtualPet
```

Or in one line on Windows:
```
g++ *.cpp -o VirtualPet && VirtualPet
```

## 💾 File Handling

Pets are saved in `pets.txt` automatically. Each line stores one pet in the format:
```
name|hunger,happiness,energy,alive|battery|storage
```
Dead pets are never written back to the file.

## 👩‍💻 Author

Maryam — Information Technology, Semester 2# oop-project---my-virtual-pet-