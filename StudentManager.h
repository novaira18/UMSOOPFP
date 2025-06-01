#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
class StudentsManager {
public:
    StudentsManager();
    ~StudentsManager();

    void showMenu();

    // Core operations
    void addStudent();
    void viewStudents() const;
    void editStudent();
    void deleteStudent();

    // Filtering
    void viewStudentsByDepartment() const;
    void viewStudentsByFaculty() const;

private:
    vector<map<string, string>> loadStudents() const;
    void saveStudents(const vector<map<string, string>>& students) const;
    int findStudentIndexById(const vector<map<string, string>>& students, const string& studentId) const;
    void showError(const string& message) const;
};