#pragma once
#ifndef PET_H
#define PET_H



#include <iostream>
#include <string>
using namespace std;

class HardwareComponent {
public:
    virtual void display() = 0;  // Pure virtual: must be overridden
    virtual ~HardwareComponent() {}
};

// ── Battery: tracks charge level and total charge cycles ─────
class Battery : public HardwareComponent {
public:
    int level;                          // Current battery percentage
    static const int LOW_THRESHOLD = 20; // Alert threshold
    static int totalChargeCycles;        // Shared across all instances

    Battery();
    Battery(const Battery& other);
    Battery& operator=(const Battery& other);

    void display() override;  // Show battery info
    void charge();            // Fully charge and increment cycle count

    ~Battery() {}
};

// ── Storage: tracks available memory space ───────────────────
class Storage : public HardwareComponent {
public:
    int space;                       // Current used storage in MB
    static const int MAX_SPACE = 500; // Maximum allowed storage

    Storage();
    Storage(const Storage& other);
    Storage& operator=(const Storage& other);

    void display() override;  // Show storage info

    ~Storage() {}
};

// ── PetState: hunger, happiness, energy + alive/dead logic ───
struct PetState {
    int hunger;     // 0 = starving,   100 = full
    int happiness;  // 0 = miserable,  100 = thrilled
    int energy;     // 0 = dead/exhausted, 100 = fully rested
    bool alive;

    PetState();

    void tick();          // Degrade stats after each action
    string label() const; // Returns "HAPPY", "SAD", "SLEEPING", or "DEAD"
    void showArt() const; // Displays matching ASCII art
    void display() const; // Prints all stat values

    // File handling: serialise to/from CSV string
    string serialise() const;
    static PetState deserialise(const string& s);
};

// ── VirtualPet: main class combining all components ──────────
class VirtualPet {
private:
    Battery  battery;   // Composition: owns a Battery
    Storage  storage;   // Composition: owns Storage
    PetState state;     // Composition: owns PetState
    string   name;      // Pet's name

    static int petCount; // Tracks total pets created

public:
    static const string SPECIES; // Species label (Pixel Creature)

    VirtualPet(string n = "Buddy");
    VirtualPet(const VirtualPet& other);
    VirtualPet& operator=(const VirtualPet& other);

    // Accessors
    Battery& getBattery();
    Storage& getStorage();
    PetState& getState();
    string    getName() const;
    bool      isAlive() const;

    void showStatus(); // Display full pet status with ASCII art

    // File handling: serialise/deserialise pet to/from a string
    string serialise() const;
    static VirtualPet deserialise(const string& line);

    static int getPetCount(); // Returns total active pets

    // Friend declarations
    friend void revealSecrets(const VirtualPet& p);
    friend class Feed;

    ~VirtualPet();
};

// Friend function: prints internal pet data (for debugging)
void revealSecrets(const VirtualPet& p);

#endif // PET_H