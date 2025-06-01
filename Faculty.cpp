#include "Faculty.h"
#include "FileUtils.h"
#include "FilePaths.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
Faculty::Faculty(const std::string& username, const std::string& password,
    const std::string& name, const std::string& gender, const std::string& dob,
    const std::string& email, const std::string& cnic, const std::string& contactNumber,
    const std::string& address)
    : User(username, password, UserType::Faculty, name, gender, dob, email, cnic, contactNumber, address)
{
}

void Faculty::showMenu() {
    int choice;
    do {
        cout << "\n=== FACULTY PANEL ===\n";
        cout << "[1] View Personal Info\n";
        cout << "[2] View Assigned Courses\n";
        cout << "[3] Mark Attendance\n";
        cout << "[4] Assign Grades\n";
        cout << "[5] View Enrolled Students\n";
        cout << "[6] View Salary\n";
        cout << "[0] Logout\n";
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: viewPersonalInfo(); break;
        case 2: viewAssignedCourses(); break;
        case 3: markAttendance(); break;
        case 4: assignGrades(); break;
        case 5: viewEnrolledStudents(); break;
        case 6: viewSalary(); break;
        case 0: cout << "Logging out...\n"; break;
        default: errorMsg("Invalid choice."); break;
        }
    } while (choice != 0);
}

void Faculty::viewPersonalInfo() {
    cout << "\n--- Personal Info ---\n";
    cout << "Username: " << username << "\n";
    cout << "Name: " << name << "\n";
    cout << "Email: " << email << "\n";
    cout << "CNIC: " << cnic << "\n";
    cout << "Contact Number: " << contactNumber << "\n";
}

void Faculty::viewAssignedCourses() {
    string coursesFile = facultyMembersFile(username) + "_courses.txt";
    showFileContents(coursesFile, "Assigned Courses");
}

void Faculty::markAttendance() {
    string courseId, studentId, date, status;
    cout << "\n--- Mark Attendance ---\n";
    cout << "Enter Course ID: ";
    getline(cin, courseId);
    cout << "Enter Student ID: ";
    getline(cin, studentId);
    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "Enter Status (Present/Absent): ";
    getline(cin, status);

    string attendanceFile = facultyMembersFile(username) + "_attendance.txt";
    ofstream fout(attendanceFile, ios::app);
    if (fout) {
        fout << courseId << "," << studentId << "," << date << "," << status << "\n";
        fout.close();
        cout << "Attendance marked successfully.\n";
    }
    else {
        errorMsg("Could not write to attendance file.");
    }
}

void Faculty::assignGrades() {
    string courseId, studentId, grade;
    cout << "\n--- Assign Grades ---\n";
    cout << "Enter Course ID: ";
    getline(cin, courseId);
    cout << "Enter Student ID: ";
    getline(cin, studentId);
    cout << "Enter Grade: ";
    getline(cin, grade);

    string gradesFile = facultyMembersFile(username) + "_grades.txt";
    ofstream fout(gradesFile, ios::app);
    if (fout) {
        fout << courseId << "," << studentId << "," << grade << "\n";
        fout.close();
        cout << "Grade assigned successfully.\n";
    }
    else {
        errorMsg("Could not write to grades file.");
    }
}

void Faculty::viewEnrolledStudents() {
    string studentsFile = facultyMembersFile(username) + "_students.txt";
    showFileContents(studentsFile, "Enrolled Students");
}

void Faculty::viewSalary() {
    // For demonstration, assume a salary file per faculty
    string salaryFile = facultyMembersFile(username) + "_salary.txt";
    ifstream fin(salaryFile);
    if (!fin) {
        errorMsg("Salary record not found.");
        return;
    }
    string line;
    cout << "\n--- Salary Details ---\n";
    bool found = false;
    while (getline(fin, line)) {
        if (!line.empty()) {
            cout << line << endl;
            found = true;
        }
    }
    if (!found) cout << "No salary record found.\n";
    fin.close();
}

void Faculty::showFileContents(const string& filename, const string& header) const {
    ifstream fin(filename);
    if (!fin) {
        cout << header << " file not found or empty.\n";
        return;
    }
    cout << "--- " << header << " ---\n";
    string line;
    bool hasContent = false;
    while (getline(fin, line)) {
        if (!line.empty()) {
            cout << line << endl;
            hasContent = true;
        }
    }
    if (!hasContent)
        cout << "No records found.\n";
    fin.close();
}

void Faculty::errorMsg(const string& msg) const {
    cout << "[Error] " << msg << "\n";
}