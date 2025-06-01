#pragma once
#include <string>
using namespace std;
class Person {
public:
    Person();
    Person(const string& name,
        const string& gender,
        const string& dob,
        const string& email,
        const string& cnic,
        const string& contactNumber,
        const string& address);

    virtual ~Person();

    // Setters
    void setName(const string& name);
    void setGender(const string& gender);
    void setDOB(const string& dob);
    void setEmail(const string& email);
    void setCnic(const string& cnic);
    void setContactNumber(const string& number);
    void setAddress(const string& address);

    // Getters
    string getName() const;
    string getGender() const;
    string getDOB() const;
    string getEmail() const;
    string getCnic() const;
    string getContactNumber() const;
    string getAddress() const;

    // Display
    virtual void displayInfo() const;

    // Serialization helpers (optional)
    virtual string toString() const;
    virtual void fromString(const string& data);

protected:
    string name;
    string gender;
    string dob;           // Date of Birth
    string email;
    string cnic;
    string contactNumber;
    string address;
};