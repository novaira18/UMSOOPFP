#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
class FacultyMembersManager {
public:
    FacultyMembersManager();
    ~FacultyMembersManager();

    void showMenu();

    // Core operations
    void addFacultyMember();
    void viewFacultyMembers() const;
    void editFacultyMember();
    void deleteFacultyMember();

private:
    vector<map<string, string>> loadFacultyMembers() const;
    void saveFacultyMembers(const vector<map<string, string>>& members) const;
    int findFacultyMemberIndexById(const vector<map<string, string>>& members, const string& memberId) const;
    void showError(const string& message) const;
};