#pragma once
#include "User.h"
#include <string>
using namespace std;
class Faculty : public User {
public:
    Faculty(const std::string& username, const std::string& password,
        const std::string& name, const std::string& gender, const std::string& dob,
        const std::string& email, const std::string& cnic, const std::string& contactNumber,
        const std::string& address);

    void showMenu() override;

private:
    // Menu actions
    void viewPersonalInfo();
    void viewAssignedCourses();
    void markAttendance();
    void assignGrades();
    void viewEnrolledStudents();
    void viewSalary();

    // Helpers for file handling
    void showFileContents(const string& filename, const string& header) const;
    void errorMsg(const string& msg) const;
};