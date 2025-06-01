#define _CRT_SECURE_NO_WARNINGS
#include "UG.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

// ========================= Events Manager =========================
void EventsManager::Add() {
    cin.ignore();
    string name, date, desc;
    cout << "Enter event name: ";
    getline(cin, name);
    cout << "Enter event date (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "Enter event description: ";
    getline(cin, desc);

    ofstream outFile("events.txt", ios::app);
    if (outFile.is_open()) {
        outFile << name << "\t" << date << "\t" << desc << "\n";
        outFile.close();
        cout << "Event added successfully.\n";
    }
    else {
        cerr << "Error: Could not open events.txt for writing.\n";
    }
}

void EventsManager::View() {
    ifstream inFile("events.txt");
    if (inFile.is_open()) {
        cout << "\n--- Events ---\n";
        string line;
        while (getline(inFile, line)) {
            cout << line << "\n";
        }
        cout << "--------------\n";
        inFile.close();
    }
    else {
        cerr << "Error: Unable to open events.txt for reading.\n";
    }
}

void EventsManager::Edit() {
    cin.ignore();
    string targetName;
    cout << "Enter event name to edit: ";
    getline(cin, targetName);

    ifstream inFile("events.txt");
    ofstream outFile("temp.txt");
    bool found = false;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name, date, desc;
        getline(ss, name, '\t');
        getline(ss, date, '\t');
        getline(ss, desc);

        if (name == targetName && !found) {
            found = true;
            cout << "Editing event: " << name << "\n";
            cout << "Enter new date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter new description: ";
            getline(cin, desc);
        }
        outFile << name << "\t" << date << "\t" << desc << "\n";
    }
    inFile.close();
    outFile.close();

    if (remove("events.txt") != 0) {
        perror("Error deleting events.txt");
    }
    if (rename("temp.txt", "events.txt") != 0) {
        perror("Error renaming temp.txt to events.txt");
    }

    if (found) {
        cout << "Event updated successfully.\n";
    }
    else {
        cout << "Event not found.\n";
    }
}

void EventsManager::Delete() {
    cin.ignore();
    string targetName;
    cout << "Enter event name to delete: ";
    getline(cin, targetName);

    ifstream inFile("events.txt");
    ofstream outFile("temp.txt");
    bool found = false;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name, date, desc;
        getline(ss, name, '\t');
        getline(ss, date, '\t');
        getline(ss, desc);

        if (name == targetName && !found) {
            found = true;
            continue; // skip (delete) this event
        }
        outFile << name << "\t" << date << "\t" << desc << "\n";
    }
    inFile.close();
    outFile.close();

    if (remove("events.txt") != 0) {
        perror("Error deleting events.txt");
    }
    if (rename("temp.txt", "events.txt") != 0) {
        perror("Error renaming temp.txt to events.txt");
    }

    if (found) {
        cout << "Event deleted successfully.\n";
    }
    else {
        cout << "Event not found.\n";
    }
}

// ========================= Notice Board =========================
void NoticeBoard::Post(const string& filename) {
    cin.ignore();
    string type, notice, date;
    cout << "Enter notice type (e.g., Urgent, General): ";
    getline(cin, type);

    cout << "Enter the notice: ";
    getline(cin, notice);

    cout << "Enter the date: ";
    getline(cin, date);

    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        outFile << date << " , " << type << " , " << notice << "\n";
        outFile.close();
        cout << "Notice posted successfully.\n";
    }
    else {
        cerr << "Error: Unable to open file for writing.\n";
    }
}

void NoticeBoard::ViewNotices() {
    const string filename = "notices.txt";
    ifstream inFile(filename);
    if (inFile.is_open()) {
        cout << "\n--- Notice Board ---\n";
        string line;
        while (getline(inFile, line)) {
            cout << line << "\n";
        }
        cout << "---------------------\n";
        inFile.close();
    }
    else {
        cerr << "Error: Unable to open file for reading.\n";
    }
}

// ========================= Library =========================
const string LIBRARY_FILE = "library.txt";

void Library::AddBook() {
    cin.ignore();
    string name, author;
    cout << "Enter Book Name: ";
    getline(cin, name);
    cout << "Enter Author Name: ";
    getline(cin, author);

    // Determine next srNo
    ifstream inFile(LIBRARY_FILE);
    int srNo = 1;
    string line;
    while (getline(inFile, line)) {
        ++srNo;
    }
    inFile.close();

    ofstream outFile(LIBRARY_FILE, ios::app);
    if (outFile.is_open()) {
        outFile << srNo << "\t" << name << "\t" << author << "\tavailable\n";
        outFile.close();
        cout << "Book added successfully.\n";
    }
    else {
        cerr << "Error: Unable to open library file for writing.\n";
    }
}

void Library::ViewBooks() {
    ifstream inFile(LIBRARY_FILE);
    if (inFile.is_open()) {
        cout << left << setw(6) << "SrNo" << setw(30) << "Book Name" << setw(25) << "Author" << "Status\n";
        cout << string(70, '-') << "\n";
        string line;
        while (getline(inFile, line)) {
            istringstream ss(line);
            string srNo, name, author, status;
            ss >> srNo;
            ss.ignore();
            getline(ss, name, '\t');
            getline(ss, author, '\t');
            ss >> status;
            cout << left << setw(6) << srNo << setw(30) << name << setw(25) << author << status << "\n";
        }
        inFile.close();
    }
    else {
        cerr << "Error: Unable to open library file for reading.\n";
    }
}

void Library::IssueBook() {
    int targetSrNo;
    cout << "Enter Serial Number of the book to issue: ";
    cin >> targetSrNo;

    ifstream inFile(LIBRARY_FILE);
    ofstream tempFile("temp.txt");
    bool found = false;
    string line;
    while (getline(inFile, line)) {
        istringstream ss(line);
        int srNo;
        string name, author, status;
        ss >> srNo;
        ss.ignore();
        getline(ss, name, '\t');
        getline(ss, author, '\t');
        ss >> status;
        if (srNo == targetSrNo) {
            if (status == "available") {
                status = "issued";
                found = true;
                cout << "Book issued successfully.\n";
            }
            else {
                cout << "Book is already issued.\n";
            }
        }
        tempFile << srNo << "\t" << name << "\t" << author << "\t" << status << "\n";
    }
    inFile.close();
    tempFile.close();

    if (remove("library.txt") != 0) {
        perror("Error deleting library.txt");
    }
    if (rename("temp.txt", "library.txt") != 0) {
        perror("Error renaming temp.txt to library.txt");
    }

    if (!found) {
        cout << "Book not found.\n";
    }
}

void Library::ReturnBook() {
    int targetSrNo;
    cout << "Enter Serial Number of the book to return: ";
    cin >> targetSrNo;

    ifstream inFile(LIBRARY_FILE);
    ofstream tempFile("temp.txt");
    bool found = false;
    string line;
    while (getline(inFile, line)) {
        istringstream ss(line);
        int srNo;
        string name, author, status;
        ss >> srNo;
        ss.ignore();
        getline(ss, name, '\t');
        getline(ss, author, '\t');
        ss >> status;
        if (srNo == targetSrNo) {
            if (status == "issued") {
                status = "available";
                found = true;
                cout << "Book returned successfully.\n";
            }
            else {
                cout << "Book was not issued.\n";
            }
        }
        tempFile << srNo << "\t" << name << "\t" << author << "\t" << status << "\n";
    }
    inFile.close();
    tempFile.close();

    if (remove("library.txt") != 0) {
        perror("Error deleting library.txt");
    }
    if (rename("temp.txt", "library.txt") != 0) {
        perror("Error renaming temp.txt to library.txt");
    }

    if (!found) {
        cout << "Book not found.\n";
    }
}

// ========================= Sports Complex =========================

string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char dt[30];
    strftime(dt, sizeof(dt), "%Y-%m-%d %H:%M:%S", ltm);
    return string(dt);
}

void SportsComplex::BookSlot() {
    cin.ignore();
    string userName, sport;
    int choice;
    cout << "Enter your name: ";
    getline(cin, userName);

    cout << "Select sport to book:\n";
    cout << "1. Cricket\n";
    cout << "2. Football\n";
    cout << "3. Table Tennis\n";
    cout << "4. Badminton\n";
    cout << "Enter choice (1-4): ";
    cin >> choice;

    switch (choice) {
    case 1: sport = "Cricket"; break;
    case 2: sport = "Football"; break;
    case 3: sport = "Table Tennis"; break;
    case 4: sport = "Badminton"; break;
    default:
        cout << "Invalid choice.\n";
        return;
    }

    string dateTime = getCurrentDateTime();

    ofstream outFile("slots.txt", ios::app);
    if (outFile.is_open()) {
        outFile << sport << "\t" << userName << "\t" << dateTime << "\n";
        outFile.close();
        cout << "Slot booked successfully for " << sport << "!\n";
    }
    else {
        cerr << "Error: Could not open slots file for writing.\n";
    }
}

void SportsComplex::ViewEquipment() {
    cout << "\n--- Sports Equipment Availability ---\n";
    cout << "Cricket:        2 sets of bats, balls, and pads\n";
    cout << "Football:       2 footballs and 2 goal nets\n";
    cout << "Table Tennis:   2 tables with paddles and balls\n";
    cout << "Badminton:      2 rackets per set and 2 shuttlecocks\n";
    cout << "--------------------------------------\n";
}

// ========================= Hostel Info =========================

struct Room {
    string roomNo;
    string status;
    string accomDate;
    string leavingDate;
};

Room parseRoomLine(const string& line) {
    stringstream ss(line);
    Room room;
    ss >> room.roomNo >> room.status >> room.accomDate >> room.leavingDate;
    return room;
}

string roomToLine(const Room& room) {
    return room.roomNo + "\t" + room.status + "\t" + room.accomDate + "\t" + room.leavingDate;
}

void HostelInfo::AllotRoom() {
    ifstream inFile("rooms.txt");
    ofstream outFile("temp.txt");

    string line;
    bool found = false;
    string date;

    cout << "Enter accommodation date (YYYY-MM-DD): ";
    cin >> date;

    while (getline(inFile, line)) {
        Room room = parseRoomLine(line);
        if (!found && room.status == "available") {
            room.status = "occupied";
            room.accomDate = date;
            room.leavingDate = "-";
            found = true;
            cout << "Room " << room.roomNo << " allotted successfully!\n";
        }
        outFile << roomToLine(room) << "\n";
    }

    inFile.close();
    outFile.close();

    if (remove("rooms.txt") != 0) {
        perror("Error deleting rooms.txt");
    }
    if (rename("temp.txt", "rooms.txt") != 0) {
        perror("Error renaming temp.txt to rooms.txt");
    }

    if (!found) {
        cout << "No available rooms found.\n";
    }
}

void HostelInfo::ViewRoomData() {
    string roomId;
    cout << "Enter room number: ";
    cin >> roomId;

    ifstream inFile("rooms.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        Room room = parseRoomLine(line);
        if (room.roomNo == roomId) {
            found = true;
            cout << "Room " << room.roomNo << " is currently " << room.status << ".\n";
            if (room.status == "occupied") {
                cout << "Accommodation Date: " << room.accomDate << "\n";
                cout << "Leaving Date: " << room.leavingDate << "\n";
            }
            break;
        }
    }
    inFile.close();

    if (!found) {
        cout << "Room not found.\n";
    }
}

// ========================= Labs =========================

void LabsManager::AddOrUpdateCompLab() {
    cin.ignore();
    string labInfo;
    cout << "Enter info for Computer Lab: ";
    getline(cin, labInfo);

    ofstream outFile("comp_lab.txt", ios::app);
    if (outFile.is_open()) {
        outFile << labInfo << "\n";
        outFile.close();
        cout << "Computer Lab info added/updated.\n";
    }
    else {
        cerr << "Error: Could not open comp_lab.txt for writing.\n";
    }
}

void LabsManager::AddOrUpdatePhysicsLab() {
    cin.ignore();
    string labInfo;
    cout << "Enter info for Physics Lab: ";
    getline(cin, labInfo);

    ofstream outFile("physics_lab.txt", ios::app);
    if (outFile.is_open()) {
        outFile << labInfo << "\n";
        outFile.close();
        cout << "Physics Lab info added/updated.\n";
    }
    else {
        cerr << "Error: Could not open physics_lab.txt for writing.\n";
    }
}

// ========================= Transport Info =========================
void TransportInfo::RegisterTransport() {
    cin.ignore();
    string studentName, busRoute;
    cout << "Enter your name: ";
    getline(cin, studentName);
    cout << "Enter bus route: ";
    getline(cin, busRoute);

    ofstream outFile("transport.txt", ios::app);
    if (outFile.is_open()) {
        outFile << studentName << "\t" << busRoute << "\n";
        outFile.close();
        cout << "Transport registered successfully.\n";
    }
    else {
        cerr << "Error: Could not open transport.txt for writing.\n";
    }
}

void TransportInfo::ViewBusRoutes() {
    ifstream inFile("transport.txt");
    if (inFile.is_open()) {
        cout << "\n--- Registered Bus Routes ---\n";
        string line;
        while (getline(inFile, line)) {
            cout << line << "\n";
        }
        cout << "-----------------------------\n";
        inFile.close();
    }
    else {
        cerr << "Error: Unable to open transport.txt for reading.\n";
    }
}