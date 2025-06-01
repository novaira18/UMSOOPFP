#include "FacultyManager.h"
#include "FilePaths.h"
#include "FileUtils.h"
#include <iostream>
#include <algorithm>
using namespace std;
FacultyManager::FacultyManager() {}
FacultyManager::~FacultyManager() {}

void FacultyManager::showMenu() {
    int choice;
    do {
        cout << "\n=== Faculty Management ===\n"
            << "[1] Add Faculty\n"
            << "[2] View Faculties\n"
            << "[3] Edit Faculty\n"
            << "[4] Delete Faculty\n"
            << "[5] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addFaculty(); break;
        case 2: viewFaculties(); break;
        case 3: editFaculty(); break;
        case 4: deleteFaculty(); break;
        case 5: break;
        default: showError("Invalid option.");
        }
    } while (choice != 5);
}

void FacultyManager::addFaculty() {
    vector<map<string, string>> faculties = loadFaculties();
    map<string, string> newFaculty;

    string id, name, dean;
    cout << "Enter Faculty ID: ";
    getline(cin, id);
    cout << "Enter Faculty Name: ";
    getline(cin, name);
    cout << "Enter Dean Name: ";
    getline(cin, dean);

    // Check for duplicate ID
    if (findFacultyIndexById(faculties, id) != -1) {
        showError("Faculty ID already exists.");
        return;
    }

    newFaculty["ID"] = id;
    newFaculty["Name"] = name;
    newFaculty["Dean"] = dean;
    faculties.push_back(newFaculty);
    saveFaculties(faculties);

    cout << "Faculty added successfully.\n";
}

void FacultyManager::viewFaculties() const {
    auto faculties = loadFaculties();
    if (faculties.empty()) {
        cout << "No faculties found.\n";
        return;
    }
    cout << "\nList of Faculties:\n";
    for (const auto& faculty : faculties) {
        cout << "ID: " << faculty.at("ID")
            << ", Name: " << faculty.at("Name")
            << ", Dean: " << faculty.at("Dean") << endl;
    }
}

void FacultyManager::editFaculty() {
    vector<map<string, string>> faculties = loadFaculties();
    if (faculties.empty()) {
        showError("No faculties to edit.");
        return;
    }
    string id;
    cout << "Enter Faculty ID to edit: ";
    getline(cin, id);
    int idx = findFacultyIndexById(faculties, id);
    if (idx == -1) {
        showError("Faculty not found.");
        return;
    }

    string name, dean;
    cout << "Enter new name [" << faculties[idx]["Name"] << "]: ";
    getline(cin, name);
    cout << "Enter new dean [" << faculties[idx]["Dean"] << "]: ";
    getline(cin, dean);

    if (!name.empty()) faculties[idx]["Name"] = name;
    if (!dean.empty()) faculties[idx]["Dean"] = dean;
    saveFaculties(faculties);
    cout << "Faculty updated successfully.\n";
}

void FacultyManager::deleteFaculty() {
    vector<map<string, string>> faculties = loadFaculties();
    if (faculties.empty()) {
        showError("No faculties to delete.");
        return;
    }
    string id;
    cout << "Enter Faculty ID to delete: ";
    getline(cin, id);
    int idx = findFacultyIndexById(faculties, id);
    if (idx == -1) {
        showError("Faculty not found.");
        return;
    }

    faculties.erase(faculties.begin() + idx);
    saveFaculties(faculties);
    cout << "Faculty deleted successfully.\n";
}

// ======= Helper Functions =======

vector<map<string, string>> FacultyManager::loadFaculties() const {
    return readCSV(FACULTY_DATA_FILE);
}

void FacultyManager::saveFaculties(const vector<map<string, string>>& faculties) const {
    writeCSV(FACULTY_DATA_FILE, faculties);
}

int FacultyManager::findFacultyIndexById(const vector<map<string, string>>& faculties, const string& facultyId) const {
    for (size_t i = 0; i < faculties.size(); ++i) {
        if (faculties[i].at("ID") == facultyId) return static_cast<int>(i);
    }
    return -1;
}

void FacultyManager::showError(const string& message) const {
    cerr << "[ERROR] " << message << endl;
}