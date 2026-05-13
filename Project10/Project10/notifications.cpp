

#include "Notifications.h"
#include <iostream>
using namespace std;


// Generic notification display
void NotificationBase::show(string msg) {
    cout << "  [Notification]: " << msg << "\n";
}


// Battery-specific alert label
void BatteryNotification::show(string msg) {
    cout << "  [Battery Alert]: " << msg << "\n";
}

// Checks if battery is at or below the low threshold.
// If so, alerts the user and offers to charge immediately.
void BatteryNotification::check(VirtualPet& p) {
    if (p.getBattery().level <= Battery::LOW_THRESHOLD) {
        show("Battery low! (" + to_string(Battery::LOW_THRESHOLD) + "% threshold)");
        cout << "  Charge now? (C to confirm): ";
        char ch;
        cin >> ch;
        if (ch == 'C' || ch == 'c') {
            p.getBattery().charge();
        }
    }
}