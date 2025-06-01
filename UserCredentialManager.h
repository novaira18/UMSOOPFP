#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
class UserCredentialsManager {
public:
    UserCredentialsManager();
    ~UserCredentialsManager();

    void showMenu();

    // Core operation
    void changePassword();

private:
    vector<map<string, string>> loadCredentials() const;
    void saveCredentials(const vector<map<string, string>>& creds) const;
    int findUserIndexByUsername(const vector<map<string, string>>& creds, const string& username) const;
    void showError(const string& message) const;
    void showSuccess(const string& message) const;
   
};