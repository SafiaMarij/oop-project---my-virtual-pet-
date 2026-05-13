#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H


#include "Pet.h"
#include <vector>
#include <string>
using namespace std;

class FileManager {
public:
    static const string SAVE_FILE; // Name of the persistence file

    FileManager();
    FileManager(const FileManager&);

    // Load all pets stored in the file
    vector<VirtualPet> loadAll();

    // Overwrite file with updated pet list (dead pets are excluded)
    void saveAll(const vector<VirtualPet>& pets);

    // Append a single new pet to the file
    void appendPet(const VirtualPet& p);

    // Remove a pet by name; returns true if found and removed
    bool removePet(const string& petName);
};

#endif // FILEMANAGER_H