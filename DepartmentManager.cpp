#include "DepartmentManager.h"
#include "FilePaths.h"
#include "FileUtils.h"
#include <iostream>
#include <algorithm>
using namespace std;
DepartmentsManager::DepartmentsManager() {}
DepartmentsManager::~DepartmentsManager() {}

void DepartmentsManager::showMenu() {
    int choice;
    do {
        cout << "\n=== Departments Management ===\n"
            << "[1] Add Department to Faculty\n"
            << "[2] View Departments\n"
            << "[3] Edit Department\n"
            << "[4] Delete Department\n"
            << "[5] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addDepartment(); break;
        case 2: viewDepartments(); break;
        case 3: editDepartment(); break;
        case 4: deleteDepartment(); break;
        case 5: break;
        default: showError("Invalid option.");
        }
    } while (choice != 5);
}

void DepartmentsManager::addDepartment() {
    auto depts = loadDepartments();
    map<string, string> newDept;

    string id, name, facultyId;
    cout << "Enter Department ID: ";
    getline(cin, id);
    cout << "Enter Department Name: ";
    getline(cin, name);
    cout << "Enter Faculty ID: ";
    getline(cin, facultyId);

    // Check for duplicate Department ID
    if (findDepartmentIndexById(depts, id) != -1) {
        showError("Department ID already exists.");
        return;
    }

    newDept["ID"] = id;
    newDept["Name"] = name;
    newDept["FacultyID"] = facultyId;
    depts.push_back(newDept);
    saveDepartments(depts);

    cout << "Department added successfully.\n";
}

void DepartmentsManager::viewDepartments() const {
    auto depts = loadDepartments();
    if (depts.empty()) {
        cout << "No departments found.\n";
        return;
    }
    cout << "\nList of Departments:\n";
    for (const auto& dept : depts) {
        cout << "ID: " << dept.at("ID")
            << ", Name: " << dept.at("Name")
            << ", FacultyID: " << dept.at("FacultyID") << endl;
    }
}

void DepartmentsManager::editDepartment() {
    auto depts = loadDepartments();
    if (depts.empty()) {
        showError("No departments to edit.");
        return;
    }
    string id;
    cout << "Enter Department ID to edit: ";
    getline(cin, id);
    int idx = findDepartmentIndexById(depts, id);
    if (idx == -1) {
        showError("Department not found.");
        return;
    }

    string name, facultyId;
    cout << "Enter new name [" << depts[idx]["Name"] << "]: ";
    getline(cin, name);
    cout << "Enter new FacultyID [" << depts[idx]["FacultyID"] << "]: ";
    getline(cin, facultyId);

    if (!name.empty()) depts[idx]["Name"] = name;
    if (!facultyId.empty()) depts[idx]["FacultyID"] = facultyId;
    saveDepartments(depts);
    cout << "Department updated successfully.\n";
}

void DepartmentsManager::deleteDepartment() {
    auto depts = loadDepartments();
    if (depts.empty()) {
        showError("No departments to delete.");
        return;
    }
    string id;
    cout << "Enter Department ID to delete: ";
    getline(cin, id);
    int idx = findDepartmentIndexById(depts, id);
    if (idx == -1) {
        showError("Department not found.");
        return;
    }

    depts.erase(depts.begin() + idx);
    saveDepartments(depts);
    cout << "Department deleted successfully.\n";
}

// ======= Helper Functions =======

vector<map<string, string>> DepartmentsManager::loadDepartments() const {
    return readCSV(DEPARTMENT_DATA_FILE);
}

void DepartmentsManager::saveDepartments(const vector<map<string, string>>& depts) const {
    writeCSV(DEPARTMENT_DATA_FILE, depts);
}

int DepartmentsManager::findDepartmentIndexById(const vector<map<string, string>>& depts, const string& deptId) const {
    for (size_t i = 0; i < depts.size(); ++i) {
        if (depts[i].at("ID") == deptId) return static_cast<int>(i);
    }
    return -1;
}

void DepartmentsManager::showError(const string& message) const {
    cerr << "[ERROR] " << message << endl;
}