#include "Utilities.h"
#include <conio.h>
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>
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

//void clearScreen() {
//#ifdef _WIN32
//    system("cls");
//#else
//    system("clear");
//#endif
//}
void clearScreen() {
    system("cls");
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


void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}



void showLoading(const string& message, int dotCount, int delayMs) {
    cout << message;
    for (int i = 0; i < dotCount; ++i) {
        cout << ".";
        cout.flush();
        Sleep(delayMs);
    }
    cout << endl;
}

void printCentered(const string& text, int width) {
    int padding = (width - text.length()) / 2;
    for (int i = 0; i < padding; ++i) cout << " ";
    cout << text << endl;
}

void displayLogo() {
    clearScreen();
    setColor(6);
    cout << R"(     
                                         ||         || ||||      ||||  |||||||||||
                                         ||         || || ||    || || ||
                                         ||         || ||  ||  ||  ||  ||
                                         ||         || ||   ||||   ||   ||||||||||
                                         ||         || ||    ||    ||            ||
                                         ||         || ||          ||           ||   
                                         ||||||||||||| ||          ||  ||||||||||         
                                           University    Management      System
)" << endl;
    setColor(7);
}

void welcomeMessage(const string& audience) {
    cout << "\t\t\t\t\t************************************" << endl;
    cout << "\t\t\t\t\t*                                  *" << endl;
    cout << "\t\t\t\t\t*     WELCOME TO " << setw(16) << left << audience << "*" << endl;
    cout << "\t\t\t\t\t*          DEPARTMENT              *" << endl;
    cout << "\t\t\t\t\t*                                  *" << endl;
    cout << "\t\t\t\t\t************************************" << endl;
}

void pressAnyKeyToContinue() {
    cout << "\nPress any key to continue...";
    _getch();
}

void displayFile(const string& filename, int color) {
    setColor(color);
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        setColor(7);
        return;
    }
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
    setColor(7);
}

void fancyDivider(int width, char ch) {
    for (int i = 0; i < width; ++i) cout << ch;
    cout << endl;
}

void showProgressBar(const string& message, int width, int durationMs) {
    cout << message << " [";
    cout.flush();
    int steps = width;
    int sleepPerStep = durationMs / steps;
    for (int i = 0; i < steps; ++i) {
        cout << char(219);
        cout.flush();
        Sleep(sleepPerStep);
    }
    cout << "] Done!" << endl;
}

void fadeInText(const string& text, int delayMs, int color) {
    setColor(color);
    for (char c : text) {
        cout << c << flush;
        Sleep(delayMs);
    }
    cout << endl;
    setColor(7);
}
