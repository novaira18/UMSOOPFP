#include "Admin.h"
#include "FacultyManager.h"
#include "DepartmentManager.h"
#include "StudentManager.h"
#include "FacultyMemberManager.h"
#include "CourseManager.h"
#include "UserCredentialManager.h"
#include "UGManager.h"
#include "SocietyManager.h"
#include <iostream>
using namespace std;
Admin::Admin() {
    facultyManager = new FacultyManager();
    departmentsManager = new DepartmentsManager();
    studentsManager = new StudentsManager();
    facultyMembersManager = new FacultyMembersManager();
    coursesManager = new CoursesManager();
    userCredentialsManager = new UserCredentialsManager();
    ugManager = new UGManager();
    societyManager = new SocietyManager();
}

Admin::~Admin() {
    delete facultyManager;
    delete departmentsManager;
    delete studentsManager;
    delete facultyMembersManager;
    delete coursesManager;
    delete userCredentialsManager;
    delete ugManager;
    delete societyManager;
}

void Admin::showMenu() {
    int choice;
    do {
        cout << "\n=== ADMIN PANEL ===\n"
            << "[1] Manage Faculties\n"
            << "[2] Manage Departments\n"
            << "[3] Manage Students\n"
            << "[4] Manage Faculty Members\n"
            << "[5] Courses Management\n"
            << "[6] Manage User Credentials\n"
            << "[7] University General Management\n"
            << "[8] Societies Management\n"
            << "[9] Logout\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: facultyManager->showMenu(); break;
        case 2: departmentsManager->showMenu(); break;
        case 3: studentsManager->showMenu(); break;
        case 4: facultyMembersManager->showMenu(); break;
        case 5: coursesManager->showMenu(); break;
        case 6: userCredentialsManager->showMenu(); break;
        case 7: ugManager->showMenu(); break;
        case 8: societyManager->showMenu(); break;
        case 9: cout << "Logging out...\n"; break;
        default: showError("Invalid option.");
        }
    } while (choice != 9);
}

void Admin::showError(const string& message) const {
    cerr << "[ERROR] " << message << endl;
}