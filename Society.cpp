#include "Society.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

// ====================== MemberManagement =========================

void MemberManagement::ViewMembers() {
    ifstream inFile("members.txt");
    if (!inFile) {
        cerr << "Error: Could not open members.txt\n";
        return;
    }

    memberNames.clear();
    memberRoles.clear();

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name, role;
        if (getline(ss, name, ',') && getline(ss, role)) {
            memberNames.push_back(name);
            memberRoles[name] = role;
        }
    }
    inFile.close();

    cout << "\nMembers of " << societyName << ":\n";
    if (memberNames.empty()) {
        cout << "No members found.\n";
        return;
    }
    for (const string& name : memberNames) {
        cout << "- " << name << " (" << memberRoles[name] << ")\n";
    }
}

void MemberManagement::addMembers() {
    string name, role;
    cout << "Enter member name: ";
    getline(cin, name);
    cout << "Enter member role: ";
    getline(cin, role);

    ofstream outFile("members.txt", ios::app);
    if (!outFile) {
        cerr << "Error: Could not open members.txt for writing.\n";
        return;
    }
    outFile << name << "," << role << "\n";
    outFile.close();

    cout << "Member '" << name << "' with role '" << role << "' added successfully.\n";
}

void MemberManagement::Logout() {
    cout << "\nLogging out from " << societyName << " management panel...\n";
    cout << "Thank you for managing the society. Goodbye!\n";
}

// ====================== EventManager =========================

void EventManager::AddEvents() {
    Event newEvent;
    cout << "Enter event title: ";
    getline(cin, newEvent.title);
    cout << "Enter event date (YYYY-MM-DD): ";
    getline(cin, newEvent.date);
    cout << "Enter event location: ";
    getline(cin, newEvent.location);
    cout << "Enter event description: ";
    getline(cin, newEvent.description);
    newEvent.isApproved = false;

    pendingApprovalEvents.push_back(newEvent);

    ofstream outFile("pending_events.txt", ios::app);
    if (!outFile) {
        cerr << "Error: Could not open pending_events.txt for writing.\n";
        return;
    }
    outFile << newEvent.title << "|"
        << newEvent.date << "|"
        << newEvent.location << "|"
        << newEvent.description << "|"
        << (newEvent.isApproved ? "1" : "0") << "\n";
    outFile.close();

    cout << "Event added and pending approval.\n";
}

void EventManager::loadPendingEvents() {
    pendingApprovalEvents.clear();
    ifstream inFile("pending_events.txt");
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        Event e;
        string approvedStr;
        getline(ss, e.title, '|');
        getline(ss, e.date, '|');
        getline(ss, e.location, '|');
        getline(ss, e.description, '|');
        getline(ss, approvedStr);
        e.isApproved = (approvedStr == "1" || approvedStr == "true");
        pendingApprovalEvents.push_back(e);
    }
    inFile.close();
}

void EventManager::RequestApprovalForEvents() {
    loadPendingEvents();
    if (pendingApprovalEvents.empty()) {
        cout << "No pending events for approval.\n";
        return;
    }

    cout << "\nPending Events:\n";
    for (size_t i = 0; i < pendingApprovalEvents.size(); ++i) {
        const Event& e = pendingApprovalEvents[i];
        cout << i + 1 << ". " << e.title << " on " << e.date << " at " << e.location << "\n";
        cout << "   Description: " << e.description << "\n";
    }

    cout << "Enter the number of the event to approve (0 to cancel): ";
    int choice;
    cin >> choice;
    cin.ignore();
    if (choice <= 0 || choice > (int)pendingApprovalEvents.size()) {
        cout << "Approval cancelled or invalid choice.\n";
        return;
    }

    // Approve the event
    pendingApprovalEvents[choice - 1].isApproved = true;
    eventList.push_back(pendingApprovalEvents[choice - 1]);
    pendingApprovalEvents.erase(pendingApprovalEvents.begin() + (choice - 1));
    cout << "Event approved successfully.\n";

    // Rewrite pending_events.txt
    ofstream pendingFile("pending_events.txt");
    if (!pendingFile) {
        cerr << "Error: Could not open pending_events.txt to update.\n";
        return;
    }
    for (const auto& e : pendingApprovalEvents) {
        pendingFile << e.title << "|" << e.date << "|" << e.location << "|" << e.description << "|" << (e.isApproved ? "1" : "0") << "\n";
    }
    pendingFile.close();

    // Append approved event to events.txt
    ofstream approvedFile("events.txt", ios::app);
    if (!approvedFile) {
        cerr << "Error: Could not open events.txt for writing.\n";
        return;
    }
    const Event& approvedEvent = eventList.back();
    approvedFile << approvedEvent.title << "|" << approvedEvent.date << "|" << approvedEvent.location << "|" << approvedEvent.description << "|" << (approvedEvent.isApproved ? "1" : "0") << "\n";
    approvedFile.close();
}

void EventManager::ViewPreviousEvents() {
    eventList.clear();
    ifstream inFile("events.txt");
    if (!inFile) {
        cout << "No approved events found.\n";
        return;
    }
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        Event e;
        string approvedStr;
        getline(ss, e.title, '|');
        getline(ss, e.date, '|');
        getline(ss, e.location, '|');
        getline(ss, e.description, '|');
        getline(ss, approvedStr);
        e.isApproved = (approvedStr == "1" || approvedStr == "true");
        eventList.push_back(e);
    }
    inFile.close();

    if (eventList.empty()) {
        cout << "No approved events to display.\n";
        return;
    }

    cout << "\nApproved Events:\n";
    for (const auto& e : eventList) {
        cout << "- " << e.title << " on " << e.date << " at " << e.location << "\n";
        cout << "  Description: " << e.description << "\n\n";
    }
}

void EventManager::Logout()
{
}

// ======================= MENU EXAMPLE =============================

void SocietyMenu(MemberManagement& memberMgr, EventManager& eventMgr) {
    int choice;
    do {
        cout << "\n=== SOCIETY MENU ===\n";
        cout << "[1] View Members\n";
        cout << "[2] Add Members\n";
        cout << "[3] Add Events\n";
        cout << "[4] Request Approval for Events\n";
        cout << "[5] View Previous Events\n";
        cout << "[0] Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: memberMgr.ViewMembers(); break;
        case 2: memberMgr.addMembers(); break;
        case 3: eventMgr.AddEvents(); break;
        case 4: eventMgr.RequestApprovalForEvents(); break;
        case 5: eventMgr.ViewPreviousEvents(); break;
        case 0: memberMgr.Logout(); break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}