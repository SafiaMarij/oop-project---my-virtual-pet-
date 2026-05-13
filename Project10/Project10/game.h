#pragma once
#ifndef GAME_H
#define GAME_H



#include "Pet.h"
#include "Actions.h"
#include "FileManager.h"
#include "Notifications.h"
#include <vector>
using namespace std;

// UI helper functions (defined in Game.cpp)
void clearInput();
void printHeader();
void printMenu();

// ── Game: main controller class ───────────────────────────────
class Game {
private:
    FileManager         fileManager; // Handles all file I/O
    BatteryNotification bn;          // Handles battery alerts

    // Helper: prompt user for a pet name
    string askPetName(const string& prompt);

    // Helper: find a pet by name in a vector; returns index or -1
    int findPet(vector<VirtualPet>& pets, const string& name);

    // Helper: load, apply action, handle death, save back to file
    void doAction(Action& action);

    // Menu action handlers
    void createPet();   // Option 1
    void viewAll();     // Option 2
    void searchPet();   // Option 3
    void viewStatus();  // Option 7
    void deletePet();   // Option 8

public:
    Game();

    // Main game loop — runs until user chooses to exit
    void run();

    ~Game() {}
};

#endif // GAME_H