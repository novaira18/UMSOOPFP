#pragma once
#include <string>
using namespace std;
// Forward declarations for all manager classes
class FacultyManager;
class DepartmentsManager;
class StudentsManager;
class FacultyMembersManager;
class CoursesManager;
class UserCredentialsManager;
class UGManager;
class SocietyManager;

class Admin {
public:
    Admin();
    ~Admin();

    // Entry point for admin interface
    void showMenu();

private:
    FacultyManager* facultyManager;
    DepartmentsManager* departmentsManager;
    StudentsManager* studentsManager;
    FacultyMembersManager* facultyMembersManager;
    CoursesManager* coursesManager;
    UserCredentialsManager* userCredentialsManager;
    UGManager* ugManager;
    SocietyManager* societyManager;

    // Utility: error display (optional, can rely on FileUtils/FilePaths for I/O)
    void showError(const string& message) const;
};