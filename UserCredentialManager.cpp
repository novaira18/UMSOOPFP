#include "UserCredentialManager.h"
#include "FilePaths.h"
#include "FileUtils.h"
#include <iostream>
#include <algorithm>
using namespace std;
UserCredentialsManager::UserCredentialsManager() {}
UserCredentialsManager::~UserCredentialsManager() {}

void UserCredentialsManager::showMenu() {
    int choice;
    do {
        cout << "\n=== User Credentials Management ===\n"
            << "[1] Change Password\n"
            << "[2] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: changePassword(); break;
        case 2: break;
        default: showError("Invalid option.");
        }
    } while (choice != 2);
}

void UserCredentialsManager::changePassword() {
    auto creds = loadCredentials();
    if (creds.empty()) {
        showError("No credentials found.");
        return;
    }
    string username;
    cout << "Enter Username: ";
    getline(cin, username);

    int idx = findUserIndexByUsername(creds, username);
    if (idx == -1) {
        showError("Username not found.");
        return;
    }

    string oldPassword, newPassword, confirmNewPassword;
    cout << "Enter Old Password: ";
    oldPassword = maskedInput();
    if (creds[idx]["Password"] != oldPassword) {
        showError("Old password is incorrect.");
        return;
    }

    cout << "Enter New Password: ";
    newPassword = maskedInput();
    cout << "Confirm New Password: ";
    confirmNewPassword = maskedInput();

    if (newPassword != confirmNewPassword) {
        showError("New passwords do not match.");
        return;
    }

    creds[idx]["Password"] = newPassword;
    saveCredentials(creds);
    showSuccess("Password changed successfully.");
}

// ======= Helper Functions =======

vector<map<string, string>> UserCredentialsManager::loadCredentials() const {
    return readCSV(CREDENTIALS_FILE);
}

void UserCredentialsManager::saveCredentials(const vector<map<string, string>>& creds) const {
    writeCSV(CREDENTIALS_FILE, creds);
}

int UserCredentialsManager::findUserIndexByUsername(const vector<map<string, string>>& creds, const string& username) const {
    for (size_t i = 0; i < creds.size(); ++i) {
        if (creds[i].at("Username") == username)
            return static_cast<int>(i);
    }
    return -1;
}

void UserCredentialsManager::showError(const string& message) const {
    cerr << "[ERROR] " << message << endl;
}

void UserCredentialsManager::showSuccess(const string& message) const {
    cout << "[SUCCESS] " << message << endl;
}