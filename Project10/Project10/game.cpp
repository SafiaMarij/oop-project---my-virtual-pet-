


#include "Game.h"
#include "AsciiArt.h"
#include <iostream>
#include <limits>
using namespace std;

// ── UI Helpers ────────────────────────────────────────────────

// Clears any bad/leftover input from the stream
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Prints the top banner of the application
void printHeader() {
    cout << "\n";
    cout << "  ╔══════════════════════════════════╗\n";
    cout << "  ║      VIRTUAL PET SYSTEM          ║\n";
    cout << "  ║      Species: Pixel Creature      ║\n";
    cout << "  ╚══════════════════════════════════╝\n";
}

// Prints the main menu options
void printMenu() {
    cout << "\n";
    cout << "  ┌──────────────────────────────────┐\n";
    cout << "  │           MAIN MENU              │\n";
    cout << "  ├──────────────────────────────────┤\n";
    cout << "  │  1.  Create Pet                  │\n";
    cout << "  │  2.  View All Pets               │\n";
    cout << "  │  3.  Search Pet by Name          │\n";
    cout << "  │  4.  Feed Pet                    │\n";
    cout << "  │  5.  Play With Pet               │\n";
    cout << "  │  6.  Let Pet Sleep               │\n";
    cout << "  │  7.  View Pet Status             │\n";
    cout << "  │  8.  Delete Pet                  │\n";
    cout << "  │  9.  Exit                        │\n";
    cout << "  └──────────────────────────────────┘\n";
    cout << "  Enter choice: ";
}

// ══════════════════════════════════════════════════════════════
// Game — private helpers
// ══════════════════════════════════════════════════════════════

Game::Game() {}

// Prompts user to type a pet name and returns it
string Game::askPetName(const string& prompt) {
    cout << "  " << prompt;
    string n;
    cin >> n;
    return n;
}

// Searches a vector for a pet with the given name.
// Returns the index if found, or -1 if not found.
int Game::findPet(vector<VirtualPet>& pets, const string& name) {
    for (int i = 0; i < (int)pets.size(); i++)
        if (pets[i].getName() == name) return i;
    return -1;
}

// Loads all pets, applies the given action to the named pet,
// handles death display, then saves the updated list back to file.
void Game::doAction(Action& action) {
    string name = askPetName("Enter pet name: ");
    vector<VirtualPet> pets = fileManager.loadAll();

    int idx = findPet(pets, name);
    if (idx == -1) {
        cout << "  Pet \"" << name << "\" not found.\n";
        return;
    }

    action.perform(pets[idx]);

    // If pet died during the action, show death art
    if (!pets[idx].isAlive()) {
        cout << "\n";
        showDeadPet();
        cout << "\n  " << name << " has passed away. Removing from records...\n";
    }

    fileManager.saveAll(pets); // Dead pets are excluded automatically
    bn.check(pets[idx]);       // Check if battery alert is needed
}



// Creates a new pet with the given name (no duplicates allowed)
void Game::createPet() {
    string name = askPetName("Enter new pet name: ");
    vector<VirtualPet> existing = fileManager.loadAll();

    if (findPet(existing, name) != -1) {
        cout << "  A pet named \"" << name << "\" already exists.\n";
        return;
    }

    VirtualPet p(name);
    fileManager.appendPet(p); // Save to file
    cout << "  Pet \"" << name << "\" created!\n";
    p.showStatus();
}

// Displays all pets currently saved in the file
void Game::viewAll() {
    vector<VirtualPet> pets = fileManager.loadAll();
    if (pets.empty()) {
        cout << "  No pets found.\n";
        return;
    }
    cout << "\n  ── All Pets (" << pets.size() << ") ──────────────────\n";
    for (VirtualPet& p : pets) p.showStatus();
}

// Searches for a pet by name and displays its status
void Game::searchPet() {
    string name = askPetName("Enter pet name to search: ");
    vector<VirtualPet> pets = fileManager.loadAll();
    int idx = findPet(pets, name);
    if (idx == -1) {
        cout << "  Pet \"" << name << "\" not found.\n";
        return;
    }
    pets[idx].showStatus();
}

// Shows status of a specific pet including debug (friend) info
void Game::viewStatus() {
    string name = askPetName("Enter pet name: ");
    vector<VirtualPet> pets = fileManager.loadAll();
    int idx = findPet(pets, name);
    if (idx == -1) {
        cout << "  Pet \"" << name << "\" not found.\n";
        return;
    }
    pets[idx].showStatus();
    revealSecrets(pets[idx]); // Friend function: shows private data
}

// Deletes a pet permanently from the file
void Game::deletePet() {
    string name = askPetName("Enter pet name to delete: ");
    if (fileManager.removePet(name))
        cout << "  Pet \"" << name << "\" deleted.\n";
    else
        cout << "  Pet \"" << name << "\" not found.\n";
}

// ══════════════════════════════════════════════════════════════
// Game::run — main loop
// ══════════════════════════════════════════════════════════════

void Game::run() {
    printHeader();
    int choice = 0;

    // Create action objects once; reuse them via polymorphism
    Feed  feedAction;
    Sleep sleepAction;
    Play  playAction;

    while (true) {
        printMenu();
        if (!(cin >> choice)) { clearInput(); continue; }

        switch (choice) {
        case 1: createPet();              break;
        case 2: viewAll();                break;
        case 3: searchPet();              break;
        case 4: doAction(feedAction);     break;
        case 5: doAction(playAction);     break;
        case 6: doAction(sleepAction);    break;
        case 7: viewStatus();             break;
        case 8: deletePet();              break;
        case 9:
            cout << "\n  Goodbye! Take care of your pets.\n\n";
            return;
        default:
            cout << "  Invalid choice. Please enter 1-9.\n";
        }
    }
}