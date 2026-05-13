
#include "Pet.h"
#include "AsciiArt.h"
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

// ── Static member definitions ─────────────────────────────────
int          Battery::totalChargeCycles = 0;
int          VirtualPet::petCount = 0;
const string VirtualPet::SPECIES = "Pixel Creature";



Battery::Battery() : level(LOW_THRESHOLD) {}

Battery::Battery(const Battery& other) : level(other.level) {}

Battery& Battery::operator=(const Battery& other) {
    if (this != &other) level = other.level;
    return *this;
}

// Display current battery level and total charge cycles
void Battery::display() {
    cout << "  Battery     : " << level
        << "% (Charge Cycles: " << totalChargeCycles << ")\n";
}

// Fully charges battery and increments shared charge cycle counter
void Battery::charge() {
    level = 100;
    totalChargeCycles++;
    cout << "  Battery fully charged! Cycles so far: " << totalChargeCycles << "\n";
}


Storage::Storage() : space(100) {}

Storage::Storage(const Storage& other) : space(other.space) {}

Storage& Storage::operator=(const Storage& other) {
    if (this != &other) space = other.space;
    return *this;
}

// Display current storage usage
void Storage::display() {
    cout << "  Storage     : " << space
        << " MB / " << MAX_SPACE << " MB\n";
}


// Default: pet starts healthy
PetState::PetState() : hunger(80), happiness(80), energy(80), alive(true) {}

// Called after every action — degrades all stats slightly
void PetState::tick() {
    if (!alive) return;
    hunger = max(0, hunger - 10);
    happiness = max(0, happiness - 5);
    energy = max(0, energy - 5);

    // Pet dies if hunger or energy reaches zero
    if (hunger == 0 || energy == 0) {
        alive = false;
    }
}

// Returns a descriptive label based on current stats
string PetState::label() const {
    if (!alive)                              return "DEAD";
    if (energy < 30)                         return "SLEEPING";
    if (happiness < 30 || hunger < 30)       return "SAD";
    return "HAPPY";
}

// Show the matching ASCII art for current state
void PetState::showArt() const {
    string s = label();
    if (s == "DEAD")     showDeadPet();
    else if (s == "SLEEPING") showSleepingPet();
    else if (s == "SAD")      showSadPet();
    else                      showHappyPet();
}

// Print all stat values to console
void PetState::display() const {
    cout << "  Hunger      : " << hunger << " / 100\n";
    cout << "  Happiness   : " << happiness << " / 100\n";
    cout << "  Energy      : " << energy << " / 100\n";
    cout << "  State       : " << label() << "\n";
}

// Serialise to CSV: hunger,happiness,energy,alive(1/0)
string PetState::serialise() const {
    return to_string(hunger) + "," + to_string(happiness) + ","
        + to_string(energy) + "," + to_string(alive ? 1 : 0);
}

// Deserialise from CSV string back into a PetState object
PetState PetState::deserialise(const string& s) {
    PetState ps;
    stringstream ss(s);
    string tok;
    getline(ss, tok, ','); ps.hunger = stoi(tok);
    getline(ss, tok, ','); ps.happiness = stoi(tok);
    getline(ss, tok, ','); ps.energy = stoi(tok);
    getline(ss, tok, ','); ps.alive = (stoi(tok) == 1);
    return ps;
}


// Constructor: sets name and increments pet count
VirtualPet::VirtualPet(string n) : name(n) { petCount++; }

// Copy constructor
VirtualPet::VirtualPet(const VirtualPet& other)
    : battery(other.battery), storage(other.storage),
    state(other.state), name(other.name)
{
    petCount++;
}

// Assignment operator
VirtualPet& VirtualPet::operator=(const VirtualPet& other) {
    if (this != &other) {
        battery = other.battery;
        storage = other.storage;
        state = other.state;
        name = other.name;
    }
    return *this;
}

// Accessors
Battery& VirtualPet::getBattery() { return battery; }
Storage& VirtualPet::getStorage() { return storage; }
PetState& VirtualPet::getState() { return state; }
string    VirtualPet::getName()    const { return name; }
bool      VirtualPet::isAlive()    const { return state.alive; }

// Display full pet status with ASCII art and all stats
void VirtualPet::showStatus() {
    cout << "\n";
    state.showArt();
    cout << "\n  ── " << name << " (" << SPECIES << ") ──────────────\n";
    battery.display();
    storage.display();
    state.display();
    cout << "  ─────────────────────────────────────────\n";
}

// Serialise: name|state|battery|storage
string VirtualPet::serialise() const {
    return name + "|" + state.serialise()
        + "|" + to_string(battery.level)
        + "|" + to_string(storage.space);
}

// Rebuild a VirtualPet object from a serialised string
VirtualPet VirtualPet::deserialise(const string& line) {
    stringstream ss(line);
    string tok;
    getline(ss, tok, '|'); string petName = tok;
    getline(ss, tok, '|'); PetState ps = PetState::deserialise(tok);
    getline(ss, tok, '|'); int bat = stoi(tok);
    getline(ss, tok, '|'); int sto = stoi(tok);

    VirtualPet p(petName);
    p.state = ps;
    p.battery.level = bat;
    p.storage.space = sto;
    return p;
}

int VirtualPet::getPetCount() { return petCount; }

// Destructor: decrements pet count
VirtualPet::~VirtualPet() { petCount--; }

// Friend function: prints private battery and storage info (debug)
void revealSecrets(const VirtualPet& p) {
    cout << "\n  [Debug] " << p.name
        << "  | Battery: " << p.battery.level
        << "%  | Storage: " << p.storage.space << " MB\n";
}