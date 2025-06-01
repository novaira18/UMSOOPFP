#include "FacultyMemberManager.h"
#include "FilePaths.h"
#include "FileUtils.h"
#include <iostream>
#include <algorithm>
using namespace std;
FacultyMembersManager::FacultyMembersManager() {}
FacultyMembersManager::~FacultyMembersManager() {}

void FacultyMembersManager::showMenu() {
    int choice;
    do {
        cout << "\n=== Faculty Members Management ===\n"
            << "[1] Add Faculty Member\n"
            << "[2] View Faculty Members\n"
            << "[3] Edit Faculty Member\n"
            << "[4] Delete Faculty Member\n"
            << "[5] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addFacultyMember(); break;
        case 2: viewFacultyMembers(); break;
        case 3: editFacultyMember(); break;
        case 4: deleteFacultyMember(); break;
        case 5: break;
        default: showError("Invalid option.");
        }
    } while (choice != 5);
}

void FacultyMembersManager::addFacultyMember() {
    auto members = loadFacultyMembers();
    map<string, string> newMember;

    string id, name, departmentId, facultyId, designation, email;
    cout << "Enter Faculty Member ID: ";
    getline(cin, id);
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Department ID: ";
    getline(cin, departmentId);
    cout << "Enter Faculty ID: ";
    getline(cin, facultyId);
    cout << "Enter Designation: ";
    getline(cin, designation);
    cout << "Enter Email: ";
    getline(cin, email);

    if (findFacultyMemberIndexById(members, id) != -1) {
        showError("Faculty Member ID already exists.");
        return;
    }

    newMember["ID"] = id;
    newMember["Name"] = name;
    newMember["DepartmentID"] = departmentId;
    newMember["FacultyID"] = facultyId;
    newMember["Designation"] = designation;
    newMember["Email"] = email;
    members.push_back(newMember);
    saveFacultyMembers(members);

    cout << "Faculty Member added successfully.\n";
}

void FacultyMembersManager::viewFacultyMembers() const {
    auto members = loadFacultyMembers();
    if (members.empty()) {
        cout << "No faculty members found.\n";
        return;
    }
    cout << "\nList of Faculty Members:\n";
    for (const auto& member : members) {
        cout << "ID: " << member.at("ID")
            << ", Name: " << member.at("Name")
            << ", DepartmentID: " << member.at("DepartmentID")
            << ", FacultyID: " << member.at("FacultyID")
            << ", Designation: " << member.at("Designation")
            << ", Email: " << member.at("Email") << endl;
    }
}

void FacultyMembersManager::editFacultyMember() {
    auto members = loadFacultyMembers();
    if (members.empty()) {
        showError("No faculty members to edit.");
        return;
    }
    string id;
    cout << "Enter Faculty Member ID to edit: ";
    getline(cin, id);
    int idx = findFacultyMemberIndexById(members, id);
    if (idx == -1) {
        showError("Faculty Member not found.");
        return;
    }

    string name, departmentId, facultyId, designation, email;
    cout << "Enter new name [" << members[idx]["Name"] << "]: ";
    getline(cin, name);
    cout << "Enter new DepartmentID [" << members[idx]["DepartmentID"] << "]: ";
    getline(cin, departmentId);
    cout << "Enter new FacultyID [" << members[idx]["FacultyID"] << "]: ";
    getline(cin, facultyId);
    cout << "Enter new Designation [" << members[idx]["Designation"] << "]: ";
    getline(cin, designation);
    cout << "Enter new Email [" << members[idx]["Email"] << "]: ";
    getline(cin, email);

    if (!name.empty()) members[idx]["Name"] = name;
    if (!departmentId.empty()) members[idx]["DepartmentID"] = departmentId;
    if (!facultyId.empty()) members[idx]["FacultyID"] = facultyId;
    if (!designation.empty()) members[idx]["Designation"] = designation;
    if (!email.empty()) members[idx]["Email"] = email;
    saveFacultyMembers(members);
    cout << "Faculty Member updated successfully.\n";
}

void FacultyMembersManager::deleteFacultyMember() {
    auto members = loadFacultyMembers();
    if (members.empty()) {
        showError("No faculty members to delete.");
        return;
    }
    string id;
    cout << "Enter Faculty Member ID to delete: ";
    getline(cin, id);
    int idx = findFacultyMemberIndexById(members, id);
    if (idx == -1) {
        showError("Faculty Member not found.");
        return;
    }

    members.erase(members.begin() + idx);
    saveFacultyMembers(members);
    cout << "Faculty Member deleted successfully.\n";
}

// ======= Helper Functions =======

vector<map<string, string>> FacultyMembersManager::loadFacultyMembers() const {
    // You may want to parameterize this if you use per-faculty files
    return readCSV(DATA_DIR + "faculty_members.txt");
}

void FacultyMembersManager::saveFacultyMembers(const vector<map<string, string>>& members) const {
    writeCSV(DATA_DIR + "faculty_members.txt", members);
}

int FacultyMembersManager::findFacultyMemberIndexById(const vector<map<string, string>>& members, const string& memberId) const {
    for (size_t i = 0; i < members.size(); ++i) {
        if (members[i].at("ID") == memberId) return static_cast<int>(i);
    }
    return -1;
}

void FacultyMembersManager::showError(const string& message) const {
    cerr << "[ERROR] " << message << endl;
}