#pragma once
#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H



#include "Pet.h"
#include <string>
using namespace std;

// ── Base notification class ────────────────────────────────────
class NotificationBase {
public:
    virtual void show(string msg); // Display a generic notification
    virtual ~NotificationBase() {}
};

// ── Battery notification: checks and alerts on low battery ────
class BatteryNotification : public NotificationBase {
public:
    // Override: shows a battery-specific alert label
    void show(string msg) override;

    // Checks battery level and prompts to charge if below threshold
    void check(VirtualPet& p);
};

#endif // NOTIFICATIONS_H