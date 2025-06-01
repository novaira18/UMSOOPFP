#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"
#include "FileUtils.h"
#include "FilePaths.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
using namespace std;
Student::Student(const std::string& username, const std::string& password,
    const std::string& name, const std::string& gender, const std::string& dob,
    const std::string& email, const std::string& cnic, const std::string& contactNumber,
    const std::string& address)
    : User(username, password, UserType::Student, name, gender, dob, email, cnic, contactNumber, address)
{
   
}

void Student::showMenu() {
    int choice;
    do {
        cout << "\n=== STUDENT PANEL ===\n";
        cout << "[1] View Profile\n";
        cout << "[2] View Registered Courses\n";
        cout << "[3] View Attendance\n";
        cout << "[4] View Grades\n";
        cout << "[5] View Timetable\n";
        cout << "[6] View Fee Invoice\n";
        cout << "[7] Feedback\n";
        cout << "[0] Logout\n";
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: viewProfile(); break;
        case 2: viewRegisteredCourses(); break;
        case 3: viewAttendance(); break;
        case 4: viewGrades(); break;
        case 5: viewTimetable(); break;
        case 6: viewFeeInvoice(); break;
        case 7: giveFeedback(); break;
        case 0: cout << "Logging out...\n"; break;
        default: errorMsg("Invalid choice."); break;
        }
    } while (choice != 0);
}

void Student::viewProfile() {
    cout << "\n--- Profile ---\n";
    cout << "Username: " << username << "\n";
    cout << "Name: " << name << "\n";
    cout << "Email: " << email << "\n";
    cout << "CNIC: " << cnic << "\n";
    cout << "Contact Number: " << contactNumber << "\n";
}

void Student::viewRegisteredCourses() {
    string coursesFile = "data/students/" + username + "_courses.txt";
    showFileContents(coursesFile, "Registered Courses");
}

void Student::viewAttendance() {
    string attendanceFile = "data/students/" + username + "_attendance.txt";
    showFileContents(attendanceFile, "Attendance Record");
}

void Student::viewGrades() {
    string gradesFile = "data/students/" + username + "_grades.txt";
    showFileContents(gradesFile, "Grades");
}

void Student::viewTimetable() {
    string timetableFile = "data/students/" + username + "_timetable.txt";
    showFileContents(timetableFile, "Timetable");
}

void Student::viewFeeInvoice() {
    string invoiceFile = "data/students/" + username + "_fee_invoice.txt";
    if (isInvoiceGenerationDate()) {
        generateFeeInvoice();
        cout << "(A new fee invoice has been generated for this year.)\n";
    }
    showFileContents(invoiceFile, "Fee Invoice");
}

void Student::giveFeedback() {
    string feedbackFile = "data/students/" + username + "_feedback.txt";
    string feedback;
    cout << "\n--- Feedback ---\n";
    cout << "Enter your feedback: ";
    getline(cin, feedback);

    ofstream fout(feedbackFile, ios::app);
    if (fout) {
        fout << feedback << "\n";
        fout.close();
        cout << "Thank you for your feedback!\n";
    }
    else {
        errorMsg("Could not save feedback.");
    }
}

void Student::showFileContents(const string& filename, const string& header) const {
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

void Student::errorMsg(const string& msg) const {
    cout << "[Error] " << msg << "\n";
}

// Helper to check if today is the annual invoice generation date (e.g., June 1st)
bool Student::isInvoiceGenerationDate() const {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    // Example: generate on June 1st each year
    return (now->tm_mon == 5 && now->tm_mday == 1); // tm_mon: 0=Jan, ..., 5=June
}

void Student::generateFeeInvoice() {
    string invoiceFile = "data/students/" + username + "_fee_invoice.txt";
    ofstream fout(invoiceFile, ios::app);
    if (fout) {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        fout << "Fee Invoice for Academic Year: " << (1900 + now->tm_year) << "\n";
        fout << "Student: " << name << " (" << username << ")\n";
        fout << "CNIC: " << cnic << "\n";
        fout << "Total Fee: 100,000 PKR\n"; // You can make this dynamic
        fout << "Due Date: 30 June " << (1900 + now->tm_year) << "\n";
        fout << "-------------------------\n";
        fout.close();
    }
    else {
        errorMsg("Could not generate fee invoice.");
    }
}