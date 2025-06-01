#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
// Reads a CSV file and returns a vector of map<string,string> (with header as keys)
vector<map<string, string>> readCSV(const string& filename);

// Writes a vector of map<string,string> to a CSV file using map keys as headers
void writeCSV(const string& filename, const vector<map<string, string>>& data);

// Appends a line to a file (for logs, etc.)
void appendLine(const string& filename, const string& line);

// Appends a log entry (timestamp, user, action, status)
void appendLog(const string& filename, const string& user, const string& action, const string& status);

// Masked password input (returns entered password with '*' masking, using getch)
string maskedInput();
