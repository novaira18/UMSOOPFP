#pragma once
#include "User.h"
#include <string>
using namespace std;
class Student : public User {
public:
    Student(const std::string& username, const std::string& password,
        const std::string& name, const std::string& gender, const std::string& dob,
        const std::string& email, const std::string& cnic, const std::string& contactNumber,
        const std::string& address);

    void showMenu() override;

private:
    // Menu actions
    void viewProfile();
    void viewRegisteredCourses();
    void viewAttendance();
    void viewGrades();
    void viewTimetable();
    void viewFeeInvoice();
    void giveFeedback();

    // File helpers
    void showFileContents(const string& filename, const string& header) const;
    void errorMsg(const string& msg) const;

    // Fee invoice helpers
    bool isInvoiceGenerationDate() const;
    void generateFeeInvoice();
};