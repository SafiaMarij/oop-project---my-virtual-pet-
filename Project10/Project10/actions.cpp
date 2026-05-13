

#include "Actions.h"
#include "AsciiArt.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Static counter: tracks total actions performed across the game
int Action::totalActionsPerformed = 0;

// Logs the action and increments global action counter
void Action::logAction(const string& actionName, const string& petName) {
    totalActionsPerformed++;
    cout << "  [Log] Action #" << totalActionsPerformed
        << ": " << actionName << " on " << petName << "\n";
}



Feed::Feed() {}
Feed::Feed(const Feed&) {}

// Feeding increases hunger and happiness; also boosts battery slightly
void Feed::perform(VirtualPet& p) {
    if (!p.isAlive()) { cout << "  This pet has passed away.\n"; return; }

    p.getBattery().level = min(100, p.getBattery().level + 20);
    p.getState().hunger = min(100, p.getState().hunger + 30);
    p.getState().happiness = min(100, p.getState().happiness + 10);

    cout << "  Yaaay! Fed " << p.getName()
        << "! Hunger +30, Happiness +10\n";

    p.getState().tick(); // Degrade stats after action
    logAction(getName(), p.getName());
}

string Feed::getName() { return "Feed"; }

// ══════════════════════════════════════════════════════════════
// Sleep
// ══════════════════════════════════════════════════════════════

Sleep::Sleep() {}
Sleep::Sleep(const Sleep&) {}

// Sleeping restores energy and battery level
void Sleep::perform(VirtualPet& p) {
    if (!p.isAlive()) { cout << "  This pet has passed away.\n"; return; }

    p.getBattery().level = min(100, p.getBattery().level + ENERGY_RESTORE);
    p.getState().energy = min(100, p.getState().energy + ENERGY_RESTORE);

    cout << "  " << p.getName() << " had a good rest! Energy +"
        << ENERGY_RESTORE << "\n";

    p.getState().tick(); // Degrade stats after action
    logAction(getName(), p.getName());
}

string Sleep::getName() { return "Sleep"; }


Play::Play() {}
Play::Play(const Play&) {}

// Playing boosts happiness but drains energy and battery
void Play::perform(VirtualPet& p) {
    if (!p.isAlive()) { cout << "  This pet has passed away.\n"; return; }

    p.getBattery().level = max(0, p.getBattery().level - ENERGY_COST);
    p.getState().energy = max(0, p.getState().energy - ENERGY_COST);
    p.getState().happiness = min(100, p.getState().happiness + 20);

    cout << "  Played with " << p.getName()
        << "! Happiness +20, Energy -" << ENERGY_COST << "\n";

    p.getState().tick(); // Degrade stats after action
    logAction(getName(), p.getName());
}

string Play::getName() { return "Play"; }