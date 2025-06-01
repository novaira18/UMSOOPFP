#pragma once
#include <string>

// No 'using namespace std;' in headers; use std::string explicitly

// Directory for all data files (change as needed)
const std::string DATA_DIR = "data/";

// File names
const std::string EVENTS_FILE = DATA_DIR + "events.txt";
const std::string NOTICES_FILE = DATA_DIR + "notices.txt";
const std::string LIBRARY_FILE = DATA_DIR + "library.txt";
const std::string SPORTS_FILE = DATA_DIR + "sports.txt";
const std::string HOSTELS_FILE = DATA_DIR + "hostels.txt";
const std::string LABS_FILE = DATA_DIR + "labs.txt";
const std::string TRANSPORT_FILE = DATA_DIR + "transport.txt";
const std::string MEMBERS_FILE = DATA_DIR + "society_members.txt";
const std::string FACULTY_DATA_FILE = DATA_DIR + "faculty.txt";
const std::string DEPARTMENT_DATA_FILE = DATA_DIR + "department.txt";
const std::string CREDENTIALS_FILE = DATA_DIR + "credentials.txt";
const std::string LOGS_FILE = DATA_DIR + "logs.txt";
const std::string STUDENT_DATA_FILE = DATA_DIR + "student.txt";
const std::string GENERAL_MEMBER_FILE = DATA_DIR + "general_members.txt";
const std::string SOCIETY_FILE = DATA_DIR + "societies.txt";

// Helper functions for file paths
inline std::string facultyMembersFileID(const std::string& facultyID) {
    return DATA_DIR + "faculty_" + facultyID + "_members.txt";
}
inline std::string departmentMembersFileID(const std::string& deptID) {
    return DATA_DIR + "dept_" + deptID + "_members.txt";
}
inline std::string societyMembersFileID(const std::string& societyID) {
    return DATA_DIR + "society_" + societyID + "_members.txt";
}
inline std::string studentsFile(const std::string& username) {
    return DATA_DIR + "students/" + username;
}
inline std::string facultyFile(const std::string& username) {
    return DATA_DIR + "faculty/" + username;
}
inline std::string facultyMembersFile(const std::string& username) {
    return "faculty_" + username;
}