#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include "Admin.h"
#include "Faculty.h"
#include "Student.h"
#include "UGManager.h"
#include "SocietyManager.h"
#include "Utilities.h" // Use the utilities from my previous answers!

using namespace std;

// Masked password input function
string getMaskedPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else if (isprint(ch)) {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void displayWelcomeMessage() {
    cout << "====================================\n";
    cout << "   Welcome to University Management System\n";
    cout << "====================================\n";
}

void displayLoginMenu() {
    cout << "\nSelect Login Type:\n";
    cout << "[1] Admin\n";
    cout << "[2] Faculty\n";
    cout << "[3] Student\n";
    cout << "[4] University General\n";
    cout << "[5] Society Member\n";
    cout << "[0] Exit\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;
    string username, password;

    displayWelcomeMessage();

    while (true) {
        displayLoginMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            cout << "Exiting the system. Goodbye!\n";
            break;
        }

        cout << "Enter Username: ";
        getline(cin, username);
        cout << "Enter Password: ";
        password = getMaskedPassword();

        int userIdOut = -1;
        string userType;
        switch (choice) {
        case 1: userType = "admin"; break;
        case 2: userType = "faculty"; break;
        case 3: userType = "student"; break;
        case 4: userType = "university_general"; break;
        case 5: userType = "society"; break;
        default: cout << "Invalid choice.\n"; continue;
        }

        if (validateLogin(userType, username, password, userIdOut)) {
            if (userType == "admin") {
                Admin admin;
                admin.showMenu();
            }
            else if (userType == "faculty") {
                // Fill in the required constructor arguments for Faculty!
                Faculty faculty(username, password, "", "", "", "", "", "", "");
                faculty.showMenu();
            }
            else if (userType == "student") {
                // Fill in the required constructor arguments for Student!
                Student student(username, password, "", "", "", "", "", "", "");
                student.showMenu();
            }
            else if (userType == "university_general") {
                UGManager ugMember;
                ugMember.showMenu();
            }
            else if (userType == "society") {
                SocietyManager societyMember;
                societyMember.showMenu();
            }
        }
        else {
            cout << "Invalid username or password. Please try again.\n";
        }
    }
    return 0;
}