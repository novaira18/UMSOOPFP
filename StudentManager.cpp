#include "StudentManager.h"
#include "FilePaths.h"
#include "FileUtils.h"
#include <iostream>
#include <algorithm>
using namespace std; 
StudentsManager::StudentsManager() {}
StudentsManager::~StudentsManager() {}

void StudentsManager::showMenu() {
    int choice;
    do {
        cout << "\n=== Students Management ===\n"
            << "[1] Add Student\n"
            << "[2] View Students\n"
            << "[3] Edit Student\n"
            << "[4] Delete Student\n"
            << "[5] View Students by Department\n"
            << "[6] View Students by Faculty\n"
            << "[7] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addStudent(); break;
        case 2: viewStudents(); break;
        case 3: editStudent(); break;
        case 4: deleteStudent(); break;
        case 5: viewStudentsByDepartment(); break;
        case 6: viewStudentsByFaculty(); break;
        case 7: break;
        default: showError("Invalid option.");
        }
    } while (choice != 7);
}

void StudentsManager::addStudent() {
    auto students = loadStudents();
    map<string, string> newStudent;

    string id, name, deptId, facultyId, email;
    cout << "Enter Student ID: ";
    getline(cin, id);
    cout << "Enter Student Name: ";
    getline(cin, name);
    cout << "Enter Department ID: ";
    getline(cin, deptId);
    cout << "Enter Faculty ID: ";
    getline(cin, facultyId);
    cout << "Enter Email: ";
    getline(cin, email);

    // Check for duplicate
    if (findStudentIndexById(students, id) != -1) {
        showError("Student ID already exists.");
        return;
    }

    newStudent["ID"] = id;
    newStudent["Name"] = name;
    newStudent["DepartmentID"] = deptId;
    newStudent["FacultyID"] = facultyId;
    newStudent["Email"] = email;
    students.push_back(newStudent);
    saveStudents(students);

    cout << "Student added successfully.\n";
}

void StudentsManager::viewStudents() const {
    auto students = loadStudents();
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }
    cout << "\nList of Students:\n";
    for (const auto& student : students) {
        cout << "ID: " << student.at("ID")
            << ", Name: " << student.at("Name")
            << ", DepartmentID: " << student.at("DepartmentID")
            << ", FacultyID: " << student.at("FacultyID")
            << ", Email: " << student.at("Email") << endl;
    }
}

void StudentsManager::editStudent() {
    auto students = loadStudents();
    if (students.empty()) {
        showError("No students to edit.");
        return;
    }
    string id;
    cout << "Enter Student ID to edit: ";
    getline(cin, id);
    int idx = findStudentIndexById(students, id);
    if (idx == -1) {
        showError("Student not found.");
        return;
    }

    string name, deptId, facultyId, email;
    cout << "Enter new name [" << students[idx]["Name"] << "]: ";
    getline(cin, name);
    cout << "Enter new DepartmentID [" << students[idx]["DepartmentID"] << "]: ";
    getline(cin, deptId);
    cout << "Enter new FacultyID [" << students[idx]["FacultyID"] << "]: ";
    getline(cin, facultyId);
    cout << "Enter new Email [" << students[idx]["Email"] << "]: ";
    getline(cin, email);

    if (!name.empty()) students[idx]["Name"] = name;
    if (!deptId.empty()) students[idx]["DepartmentID"] = deptId;
    if (!facultyId.empty()) students[idx]["FacultyID"] = facultyId;
    if (!email.empty()) students[idx]["Email"] = email;
    saveStudents(students);
    cout << "Student updated successfully.\n";
}

void StudentsManager::deleteStudent() {
    auto students = loadStudents();
    if (students.empty()) {
        showError("No students to delete.");
        return;
    }
    string id;
    cout << "Enter Student ID to delete: ";
    getline(cin, id);
    int idx = findStudentIndexById(students, id);
    if (idx == -1) {
        showError("Student not found.");
        return;
    }

    students.erase(students.begin() + idx);
    saveStudents(students);
    cout << "Student deleted successfully.\n";
}

void StudentsManager::viewStudentsByDepartment() const {
    string deptId;
    cout << "Enter Department ID to filter: ";
    getline(cin, deptId);

    auto students = loadStudents();
    bool found = false;
    for (const auto& student : students) {
        if (student.at("DepartmentID") == deptId) {
            if (!found) {
                cout << "\nStudents in Department " << deptId << ":\n";
                found = true;
            }
            cout << "ID: " << student.at("ID")
                << ", Name: " << student.at("Name")
                << ", FacultyID: " << student.at("FacultyID")
                << ", Email: " << student.at("Email") << endl;
        }
    }
    if (!found)
        cout << "No students found for this department.\n";
}

void StudentsManager::viewStudentsByFaculty() const {
    string facultyId;
    cout << "Enter Faculty ID to filter: ";
    getline(cin, facultyId);

    auto students = loadStudents();
    bool found = false;
    for (const auto& student : students) {
        if (student.at("FacultyID") == facultyId) {
            if (!found) {
                cout << "\nStudents in Faculty " << facultyId << ":\n";
                found = true;
            }
            cout << "ID: " << student.at("ID")
                << ", Name: " << student.at("Name")
                << ", DepartmentID: " << student.at("DepartmentID")
                << ", Email: " << student.at("Email") << endl;
        }
    }
    if (!found)
        cout << "No students found for this faculty.\n";
}

// ======= Helper Functions =======

vector<map<string, string>> StudentsManager::loadStudents() const {
    return readCSV(STUDENT_DATA_FILE);
}

void StudentsManager::saveStudents(const vector<map<string, string>>& students) const {
    writeCSV(STUDENT_DATA_FILE, students);
}

int StudentsManager::findStudentIndexById(const vector<map<string, string>>& students, const string& studentId) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].at("ID") == studentId) return static_cast<int>(i);
    }
    return -1;
}

void StudentsManager::showError(const string& message) const {
    cerr << "[ERROR] " << message << endl;
}