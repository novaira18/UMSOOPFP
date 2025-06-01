#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
// Department management for Admin panel
class DepartmentsManager {
public:
    DepartmentsManager();
    ~DepartmentsManager();

    void showMenu();

    // Core operations
    void addDepartment();
    void viewDepartments() const;
    void editDepartment();
    void deleteDepartment();

private:
    // Helpers for file I/O
    vector<map<string, string>> loadDepartments() const;
    void saveDepartments(const vector<map<string, string>>& depts) const;
    int findDepartmentIndexById(const vector<map<string, string>>& depts, const string& deptId) const;
    void showError(const string& message) const;
};