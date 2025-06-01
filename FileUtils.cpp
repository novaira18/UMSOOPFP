#define _CRT_SECURE_NO_WARNINGS
#include "FileUtils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
using namespace std;
vector<map<string, string>> readCSV(const string& filename) {
    vector<map<string, string>> result;
    ifstream fin(filename);
    if (!fin) return result;
    string line;
    vector<string> headers;
    if (getline(fin, line)) {
        stringstream ss(line);
        string item;
        while (getline(ss, item, ',')) headers.push_back(item);
    }
    while (getline(fin, line)) {
        stringstream ss(line);
        string item;
        map<string, string> row;
        for (size_t i = 0; i < headers.size(); ++i) {
            if (!getline(ss, item, ',')) item = "";
            row[headers[i]] = item;
        }
        if (!row.empty()) result.push_back(row);
    }
    fin.close();
    return result;
}

void writeCSV(const string& filename, const vector<map<string, string>>& data) {
    ofstream fout(filename, ios::trunc);
    if (data.empty()) {
        fout.close();
        return;
    }
    // Write headers
    auto& first = data[0];
    bool firstHeader = true;
    for (const auto& pair : first) {
        if (!firstHeader) fout << ",";
        fout << pair.first;
        firstHeader = false;
    }
    fout << "\n";
    // Write rows
    for (const auto& row : data) {
        bool firstVal = true;
        for (const auto& pair : first) {
            if (!firstVal) fout << ",";
            auto it = row.find(pair.first);
            fout << (it != row.end() ? it->second : "");
            firstVal = false;
        }
        fout << "\n";
    }
    fout.close();
}

void appendLine(const string& filename, const string& line) {
    ofstream fout(filename, ios::app);
    fout << line << "\n";
    fout.close();
}

void appendLog(const string& filename, const string& user, const string& action, const string& status) {
    // Format: timestamp,user,action,status
    time_t t = time(nullptr);
    char timestr[32];
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localtime(&t));
    string logline = string(timestr) + "," + user + "," + action + "," + status;
    appendLine(filename, logline);
}

string maskedInput() {
    string password;
    char ch;
#ifdef _WIN32
    while ((ch = _getch()) != '\r') { // Enter key
        if (ch == '\b') { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else if (ch == 3) { // Ctrl+C
            exit(0);
        }
        else if (isprint(ch)) {
            password += ch;
            cout << '*';
        }
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while (true) {
        ch = getchar();
        if (ch == '\n' || ch == '\r') break;
        if (ch == 127 || ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else if (ch == 3) {
            exit(0);
        }
        else if (isprint(ch)) {
            password += ch;
            cout << '*';
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    cout << endl;
    return password;
}