#include "Person.h"
#include <iostream>
#include <sstream>
using namespace std;
Person::Person()
    : name(""), gender(""), dob(""), email(""), cnic(""), contactNumber(""), address("") {
}

Person::Person(const string& name,
    const string& gender,
    const string& dob,
    const string& email,
    const string& cnic,
    const string& contactNumber,
    const string& address)
    : name(name), gender(gender), dob(dob), email(email), cnic(cnic), contactNumber(contactNumber), address(address) {
}

Person::~Person() {}

// Setters
void Person::setName(const string& name) { this->name = name; }
void Person::setGender(const string& gender) { this->gender = gender; }
void Person::setDOB(const string& dob) { this->dob = dob; }
void Person::setEmail(const string& email) { this->email = email; }
void Person::setCnic(const string& cnic) { this->cnic = cnic; }
void Person::setContactNumber(const string& number) { this->contactNumber = number; }
void Person::setAddress(const string& address) { this->address = address; }

// Getters
string Person::getName() const { return name; }
string Person::getGender() const { return gender; }
string Person::getDOB() const { return dob; }
string Person::getEmail() const { return email; }
string Person::getCnic() const { return cnic; }
string Person::getContactNumber() const { return contactNumber; }
string Person::getAddress() const { return address; }

// Display
void Person::displayInfo() const {
    cout << "Name: " << name << "\n"
        << "Gender: " << gender << "\n"
        << "Date of Birth: " << dob << "\n"
        << "Email: " << email << "\n"
        << "CNIC: " << cnic << "\n"
        << "Contact Number: " << contactNumber << "\n"
        << "Address: " << address << "\n";
}

// Optional: Serialization helpers (for file I/O)
string Person::toString() const {
    ostringstream oss;
    oss << name << "," << gender << "," << dob << "," << email << ","
        << cnic << "," << contactNumber << "," << address;
    return oss.str();
}

void Person::fromString(const string& data) {
    istringstream iss(data);
    getline(iss, name, ',');
    getline(iss, gender, ',');
    getline(iss, dob, ',');
    getline(iss, email, ',');
    getline(iss, cnic, ',');
    getline(iss, contactNumber, ',');
    getline(iss, address, ',');
}