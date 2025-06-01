#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
class SocietyManager {
public:
    SocietyManager();
    ~SocietyManager();

    void showMenu();

    // Core operations
    void addSociety();
    void viewSocieties() const;
    void editSociety();
    void deleteSociety();

    // Member management
    void addMember();
    void viewMembers() const;
    void removeMember();

private:
    vector<map<string, string>> loadSocieties() const;
    void saveSocieties(const vector<map<string, string>>& societies) const;
    int findSocietyIndexById(const vector<map<string, string>>& societies, const string& id) const;

    vector<map<string, string>> loadMembers() const;
    void saveMembers(const vector<map<string, string>>& members) const;
    int findMemberIndex(const vector<map<string, string>>& members, const string& societyId, const string& memberId) const;

    void showError(const string& message) const;
};