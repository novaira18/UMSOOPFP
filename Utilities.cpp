#include "utilities.h"
#include <iostream>
#include <cctype>
#include <algorithm>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printLine(char ch, int length) {
    for (int i = 0; i < length; i++) cout << ch;
    cout << endl;
}

std::string toLower(const std::string& str) {
    string out = str;
    transform(out.begin(), out.end(), out.begin(),
        [](unsigned char c) { return tolower(c); });
    return out;
}

void pause() {
    cout << "Press any key to continue...";
    cin.get();
}

std::string trim(const std::string& str) {
    const char* ws = " \t\n\r\f\v";
    size_t start = str.find_first_not_of(ws);
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(ws);
    return str.substr(start, end - start + 1);
}

// Dummy user files - replace with your actual files and logic
const string ADMIN_FILE = "admin_users.txt";
const string FACULTY_FILE = "faculty_users.txt";
const string STUDENT_FILE = "student_users.txt";
const string SOCIETY_FILE = "society_users.txt";
const string UGF_FILE = "university_general_users.txt";

// This is a simple file-based login validation for demonstration
bool validateLogin(const string& userType, const string& username, const string& password, int& userIdOut) {
    string filename;
    if (userType == "admin") filename = ADMIN_FILE;
    else if (userType == "faculty") filename = FACULTY_FILE;
    else if (userType == "student") filename = STUDENT_FILE;
    else if (userType == "society") filename = SOCIETY_FILE;
    else if (userType == "university_general") filename = UGF_FILE;
    else return false;

    ifstream fin(filename);
    if (!fin.is_open()) return false;

    string u, p;
    int id = 0;
    while (fin >> u >> p) {
        if (trim(u) == trim(username) && p == password) {
            userIdOut = id;
            fin.close();
            return true;
        }
        id++;
    }
    fin.close();
    return false;
}