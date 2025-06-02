#pragma once
#include <string>
using namespace std;
// Clears the console screen (Windows and Unix)
void clearScreen();

// Prints a horizontal line of a given character
void printLine(char ch = '-', int length = 60);

// Validates login credentials for a given user type.
// Returns true if credentials are correct and sets userIdOut (e.g., index or ID from storage).
bool validateLogin(const string& userType, const string& username, const string& password, int& userIdOut);

// Converts input to lowercase (utility)
string toLower(const string& str);

// Pauses the system (press any key to continue)
void pause();

// Trims whitespace from both ends of a string
string trim(const string& str);

void setColor(int color);
//void clearScreen();
void showLoading(const string& message, int dotCount = 5, int delayMs = 300);
void printCentered(const string& text, int width = 100);
void displayLogo();
void welcomeMessage(const string& audience = "USER");
void pressAnyKeyToContinue();
void displayFile(const string& filename, int color = 7);
void fancyDivider(int width = 80, char ch = '=');
void showProgressBar(const string& message, int width = 30, int durationMs = 1500);
void fadeInText(const string& text, int delayMs = 40, int color = 11);
