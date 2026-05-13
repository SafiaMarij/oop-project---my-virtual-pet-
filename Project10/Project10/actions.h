#pragma once
#ifndef ACTIONS_H
#define ACTIONS_H



#include "Pet.h"
#include <string>
using namespace std;

// ── Abstract base class for all pet actions ───────────────────
class Action {
public:
    static int totalActionsPerformed; // Shared counter for all actions

    virtual void perform(VirtualPet& p) = 0; // Pure virtual
    virtual string getName() = 0;

    virtual ~Action() {}

protected:
    // Logs each action performed (increments counter)
    void logAction(const string& actionName, const string& petName);
};

// ── Feed: increases hunger and happiness ──────────────────────
class Feed : public Action {
public:
    Feed();
    Feed(const Feed&);

    void perform(VirtualPet& p) override;
    string getName() override;

    ~Feed() {}
};

// ── Sleep: restores energy ────────────────────────────────────
class Sleep : public Action {
public:
    static const int ENERGY_RESTORE = 30; // How much energy is restored

    Sleep();
    Sleep(const Sleep&);

    void perform(VirtualPet& p) override;
    string getName() override;

    ~Sleep() {}
};

// ── Play: boosts happiness but costs energy ───────────────────
class Play : public Action {
public:
    static const int ENERGY_COST = 10; // Energy consumed during play

    Play();
    Play(const Play&);

    void perform(VirtualPet& p) override;
    string getName() override;

    ~Play() {}
};

#endif // ACTIONS_H