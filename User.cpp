#include "User.h"
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
// --- User Implementation ---

User::User()
    : Person(), username(""), password(""), role(UserType::Unknown) {
}

User::User(const string& username, const string& password, UserType role,
    const string& name, const string& gender, const string& dob,
    const string& email, const string& cnic, const string& contactNumber,
    const string& address)
    : Person(name, gender, dob, email, cnic, contactNumber, address),
    username(username), password(password), role(role) {
}

void User::setUsername(const string& username) { this->username = username; }
void User::setPassword(const string& password) { this->password = password; }
void User::setRole(UserType type) { this->role = type; }

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
UserType User::getRole() const { return role; }

// User type helpers
UserType User::stringToUserType(const string& s) {
    string lower = s;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (lower == "admin") return UserType::Admin;
    if (lower == "faculty") return UserType::Faculty;
    if (lower == "student") return UserType::Student;
    if (lower == "universitygeneral" || lower == "ugm") return UserType::UniversityGeneral;
    if (lower == "societymember" || lower == "society") return UserType::SocietyMember;
    return UserType::Unknown;
}
string User::userTypeToString(UserType t) {
    switch (t) {
    case UserType::Admin: return "Admin";
    case UserType::Faculty: return "Faculty";
    case UserType::Student: return "Student";
    case UserType::UniversityGeneral: return "UniversityGeneral";
    case UserType::SocietyMember: return "SocietyMember";
    default: return "Unknown";
    }
}

// Serialization
void User::fromString(const string& data) {
    // Expects: username,password,role,name,gender,dob,email,cnic,contact,address
    istringstream iss(data);
    string token;
    getline(iss, username, ',');
    getline(iss, password, ',');
    getline(iss, token, ','); role = stringToUserType(token);
    getline(iss, name, ',');
    getline(iss, gender, ',');
    getline(iss, dob, ',');
    getline(iss, email, ',');
    getline(iss, cnic, ',');
    getline(iss, contactNumber, ',');
    getline(iss, address, ',');
}

string User::toString() const {
    ostringstream oss;
    oss << username << "," << password << "," << userTypeToString(role) << ","
        << name << "," << gender << "," << dob << ","
        << email << "," << cnic << "," << contactNumber << "," << address;
    return oss.str();
}

// Default menu (to be extended/overridden as per role)
void User::showMenu() {
    cout << "\nWelcome, " << username << " (" << userTypeToString(role) << ")\n";
    cout << "Person Info:\n";
    displayInfo();
    cout << "Menu options would be implemented in derived classes or as needed.\n";
}

// --- Example Derived Class Implementations ---

UniversityGeneralUser::UniversityGeneralUser(const string& username, const string& password,
    const string& name, const string& gender, const string& dob,
    const string& email, const string& cnic, const string& contactNumber,
    const string& address)
    : User(username, password, UserType::UniversityGeneral, name, gender, dob, email, cnic, contactNumber, address) {
}

// Add UGM interface implementations if required

SocietyMemberUser::SocietyMemberUser(const string& username, const string& password,
    const string& name, const string& gender, const string& dob,
    const string& email, const string& cnic, const string& contactNumber,
    const string& address)
    : User(username, password, UserType::SocietyMember, name, gender, dob, email, cnic, contactNumber, address) {
}

// Add SocietyMenu interface implementations if required