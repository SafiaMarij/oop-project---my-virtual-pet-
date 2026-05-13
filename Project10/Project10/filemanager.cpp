

#include "FileManager.h"
#include <fstream>
#include <algorithm>
using namespace std;

// The file where all pet data is saved
const string FileManager::SAVE_FILE = "pets.txt";

FileManager::FileManager() {}
FileManager::FileManager(const FileManager&) {}

// Reads all pets from file and returns them as a vector.
// Returns an empty vector if file does not exist.
vector<VirtualPet> FileManager::loadAll() {
    vector<VirtualPet> pets;
    ifstream file(SAVE_FILE);
    if (!file.is_open()) return pets; // File may not exist yet

    string line;
    while (getline(file, line)) {
        if (!line.empty())
            pets.push_back(VirtualPet::deserialise(line));
    }
    file.close();
    return pets;
}

// Overwrites the file with the current list of pets.
// Dead pets are automatically excluded from saving.
void FileManager::saveAll(const vector<VirtualPet>& pets) {
    ofstream file(SAVE_FILE);
    for (const VirtualPet& p : pets) {
        if (p.isAlive()) // Only save living pets
            file << p.serialise() << "\n";
    }
    file.close();
}

// Appends a single new pet to the end of the file.
// Used when creating a new pet so existing data is preserved.
void FileManager::appendPet(const VirtualPet& p) {
    ofstream file(SAVE_FILE, ios::app); // Open in append mode
    file << p.serialise() << "\n";
    file.close();
}

// Removes a pet by name from the file.
// Returns true if the pet was found and removed, false otherwise.
bool FileManager::removePet(const string& petName) {
    vector<VirtualPet> pets = loadAll();
    int before = (int)pets.size();

    // Erase the pet with matching name
    pets.erase(
        remove_if(pets.begin(), pets.end(),
            [&](const VirtualPet& p) { return p.getName() == petName; }),
        pets.end()
    );

    if ((int)pets.size() == before) return false; // Not found

    saveAll(pets); // Write updated list back to file
    return true;
}