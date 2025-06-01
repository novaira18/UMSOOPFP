#include "SocietyManager.h"
#include "FileUtils.h"
#include "FilePaths.h"
#include <iostream>
#include <algorithm>
using namespace std;

SocietyManager::SocietyManager() {}
SocietyManager::~SocietyManager() {}

void SocietyManager::showMenu() {
    int choice;
    do {
        cout << "\n=== Society Management ===\n"
            << "[1] Add Society\n"
            << "[2] View Societies\n"
            << "[3] Edit Society\n"
            << "[4] Delete Society\n"
            << "[5] Add Member to Society\n"
            << "[6] View Society Members\n"
            << "[7] Remove Member from Society\n"
            << "[8] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addSociety(); break;
        case 2: viewSocieties(); break;
        case 3: editSociety(); break;
        case 4: deleteSociety(); break;
        case 5: addMember(); break;
        case 6: viewMembers(); break;
        case 7: removeMember(); break;
        case 8: break;
        default: showError("Invalid option.");
        }
    } while (choice != 8);
}

// ========== Society CRUD ==========

void SocietyManager::addSociety() {
    auto societies = loadSocieties();
    map<string, string> society;
    string id, name, advisor;
    cout << "Enter Society ID: ";
    getline(cin, id);
    if (findSocietyIndexById(societies, id) != -1) {
        showError("Society ID already exists.");
        return;
    }
    cout << "Enter Society Name: ";
    getline(cin, name);
    cout << "Enter Faculty Advisor Name: ";
    getline(cin, advisor);

    society["ID"] = id;
    society["Name"] = name;
    society["Advisor"] = advisor;
    societies.push_back(society);
    saveSocieties(societies);

    cout << "Society added.\n";
}

void SocietyManager::viewSocieties() const {
    auto societies = loadSocieties();
    if (societies.empty()) {
        cout << "No societies found.\n";
        return;
    }
    cout << "\nList of Societies:\n";
    for (const auto& s : societies) {
        cout << "ID: " << s.at("ID")
            << ", Name: " << s.at("Name")
            << ", Advisor: " << s.at("Advisor") << endl;
    }
}

void SocietyManager::editSociety() {
    auto societies = loadSocieties();
    if (societies.empty()) {
        showError("No societies to edit.");
        return;
    }
    string id;
    cout << "Enter Society ID to edit: ";
    getline(cin, id);
    int idx = findSocietyIndexById(societies, id);
    if (idx == -1) {
        showError("Society not found.");
        return;
    }
    string name, advisor;
    cout << "Enter new name [" << societies[idx]["Name"] << "]: ";
    getline(cin, name);
    cout << "Enter new advisor [" << societies[idx]["Advisor"] << "]: ";
    getline(cin, advisor);

    if (!name.empty()) societies[idx]["Name"] = name;
    if (!advisor.empty()) societies[idx]["Advisor"] = advisor;
    saveSocieties(societies);
    cout << "Society updated.\n";
}

void SocietyManager::deleteSociety() {
    auto societies = loadSocieties();
    if (societies.empty()) {
        showError("No societies to delete.");
        return;
    }
    string id;
    cout << "Enter Society ID to delete: ";
    getline(cin, id);
    int idx = findSocietyIndexById(societies, id);
    if (idx == -1) {
        showError("Society not found.");
        return;
    }
    societies.erase(societies.begin() + idx);
    saveSocieties(societies);

    // Also remove society members
    auto members = loadMembers();
    members.erase(
        remove_if(members.begin(), members.end(),
            [&](const map<string, string>& m) { return m.at("SocietyID") == id; }),
        members.end()
    );
    saveMembers(members);

    cout << "Society and its members deleted.\n";
}

// ========== Member Management ==========

void SocietyManager::addMember() {
    auto societies = loadSocieties();
    if (societies.empty()) {
        showError("No societies available. Add a society first.");
        return;
    }
    string societyId, memberId, memberName, role;
    cout << "Enter Society ID to add member to: ";
    getline(cin, societyId);
    if (findSocietyIndexById(societies, societyId) == -1) {
        showError("Society not found.");
        return;
    }

    auto members = loadMembers();
    cout << "Enter Member ID: ";
    getline(cin, memberId);
    if (findMemberIndex(members, societyId, memberId) != -1) {
        showError("Member already exists in this society.");
        return;
    }
    cout << "Enter Member Name: ";
    getline(cin, memberName);
    cout << "Enter Role (President/Secretary/Member/etc): ";
    getline(cin, role);

    map<string, string> member;
    member["SocietyID"] = societyId;
    member["MemberID"] = memberId;
    member["Name"] = memberName;
    member["Role"] = role;
    members.push_back(member);
    saveMembers(members);

    cout << "Member added to society.\n";
}

void SocietyManager::viewMembers() const {
    auto members = loadMembers();
    if (members.empty()) {
        cout << "No members found.\n";
        return;
    }
    string societyId;
    cout << "Enter Society ID to view members: ";
    getline(cin, societyId);
    bool found = false;
    for (const auto& m : members) {
        if (m.at("SocietyID") == societyId) {
            if (!found) {
                cout << "\nMembers of Society ID: " << societyId << endl;
                found = true;
            }
            cout << "MemberID: " << m.at("MemberID")
                << ", Name: " << m.at("Name")
                << ", Role: " << m.at("Role") << endl;
        }
    }
    if (!found)
        cout << "No members registered for this society.\n";
}

void SocietyManager::removeMember() {
    auto members = loadMembers();
    if (members.empty()) {
        showError("No members to remove.");
        return;
    }
    string societyId, memberId;
    cout << "Enter Society ID: ";
    getline(cin, societyId);
    cout << "Enter Member ID to remove: ";
    getline(cin, memberId);

    int idx = findMemberIndex(members, societyId, memberId);
    if (idx == -1) {
        showError("Member not found in the given society.");
        return;
    }
    members.erase(members.begin() + idx);
    saveMembers(members);
    cout << "Member removed from society.\n";
}

// ========== File & Helper Methods ==========

vector<map<string, string>> SocietyManager::loadSocieties() const {
    return readCSV(SOCIETY_FILE);
}

void SocietyManager::saveSocieties(const vector<map<string, string>>& societies) const {
    writeCSV(SOCIETY_FILE, societies);
}

int SocietyManager::findSocietyIndexById(const vector<map<string, string>>& societies, const string& id) const {
    for (size_t i = 0; i < societies.size(); ++i)
        if (societies[i].at("ID") == id)
            return static_cast<int>(i);
    return -1;
}

vector<map<string, string>> SocietyManager::loadMembers() const {
    return readCSV(MEMBERS_FILE);
}

void SocietyManager::saveMembers(const vector<map<string, string>>& members) const {
    writeCSV(MEMBERS_FILE, members);
}

int SocietyManager::findMemberIndex(const vector<map<string, string>>& members, const string& societyId, const string& memberId) const {
    for (size_t i = 0; i < members.size(); ++i)
        if (members[i].at("SocietyID") == societyId && members[i].at("MemberID") == memberId)
            return static_cast<int>(i);
    return -1;
}

void SocietyManager::showError(const string& message) const {
    cerr << "[ERROR] " << message << endl;
}