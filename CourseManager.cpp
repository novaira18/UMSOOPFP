#include "CourseManager.h"
#include "FilePaths.h"
#include "FileUtils.h"
#include <iostream>
#include <algorithm>
using namespace std; 
CoursesManager::CoursesManager() {}
CoursesManager::~CoursesManager() {}

void CoursesManager::showMenu() {
    int choice;
    do {
        cout << "\n=== Courses Management ===\n"
            << "[1] Add Course to Department\n"
            << "[2] Assign Course to Faculty\n"
            << "[3] Enroll Student in Course\n"
            << "[4] View Courses List\n"
            << "[5] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addCourse(); break;
        case 2: assignCourseToFaculty(); break;
        case 3: enrollStudentInCourse(); break;
        case 4: viewCourses(); break;
        case 5: break;
        default: showError("Invalid option.");
        }
    } while (choice != 5);
}

void CoursesManager::addCourse() {
    auto courses = loadCourses();
    map<string, string> newCourse;

    string id, name, deptId, credits;
    cout << "Enter Course ID: ";
    getline(cin, id);
    cout << "Enter Course Name: ";
    getline(cin, name);
    cout << "Enter Department ID: ";
    getline(cin, deptId);
    cout << "Enter Credits: ";
    getline(cin, credits);

    if (findCourseIndexById(courses, id) != -1) {
        showError("Course ID already exists.");
        return;
    }

    newCourse["ID"] = id;
    newCourse["Name"] = name;
    newCourse["DepartmentID"] = deptId;
    newCourse["Credits"] = credits;
    newCourse["FacultyID"] = "";  // Not assigned yet
    courses.push_back(newCourse);
    saveCourses(courses);

    cout << "Course added successfully.\n";
}

void CoursesManager::assignCourseToFaculty() {
    auto courses = loadCourses();
    if (courses.empty()) {
        showError("No courses available to assign.");
        return;
    }
    string courseId, facultyId;
    cout << "Enter Course ID to assign: ";
    getline(cin, courseId);
    int idx = findCourseIndexById(courses, courseId);
    if (idx == -1) {
        showError("Course not found.");
        return;
    }
    cout << "Enter Faculty ID to assign: ";
    getline(cin, facultyId);

    courses[idx]["FacultyID"] = facultyId;
    saveCourses(courses);
    cout << "Course assigned to faculty successfully.\n";
}

void CoursesManager::enrollStudentInCourse() {
    auto courses = loadCourses();
    if (courses.empty()) {
        showError("No courses available for enrollment.");
        return;
    }
    string courseId, studentId;
    cout << "Enter Course ID to enroll student in: ";
    getline(cin, courseId);
    int idx = findCourseIndexById(courses, courseId);
    if (idx == -1) {
        showError("Course not found.");
        return;
    }
    cout << "Enter Student ID to enroll: ";
    getline(cin, studentId);

    // Store enrolled students as comma-separated IDs in "Students" field
    string& enrolled = courses[idx]["Students"];
    if (!enrolled.empty()) enrolled += ",";
    enrolled += studentId;
    saveCourses(courses);
    cout << "Student enrolled in course successfully.\n";
}

void CoursesManager::viewCourses() const {
    auto courses = loadCourses();
    if (courses.empty()) {
        cout << "No courses found.\n";
        return;
    }
    cout << "\nList of Courses:\n";
    for (const auto& course : courses) {
        cout << "ID: " << course.at("ID")
            << ", Name: " << course.at("Name")
            << ", DepartmentID: " << course.at("DepartmentID")
            << ", Credits: " << course.at("Credits")
            << ", FacultyID: " << (course.at("FacultyID").empty() ? "Unassigned" : course.at("FacultyID"))
            << ", Enrolled Students: " << (course.count("Students") ? course.at("Students") : "None")
            << endl;
    }
}

// ======= Helper Functions =======

vector<map<string, string>> CoursesManager::loadCourses() const {
    return readCSV(DATA_DIR + "courses.txt");
}

void CoursesManager::saveCourses(const vector<map<string, string>>& courses) const {
    writeCSV(DATA_DIR + "courses.txt", courses);
}

int CoursesManager::findCourseIndexById(const vector<map<string, string>>& courses, const string& courseId) const {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i].at("ID") == courseId) return static_cast<int>(i);
    }
    return -1;
}

void CoursesManager::showError(const string& message) const {
    cerr << "[ERROR] " << message << endl;
}