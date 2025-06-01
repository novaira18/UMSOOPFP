#pragma once
#include "Person.h"
#include <string>
using namespace std;
// Forward declarations if you use interfaces/abstract classes
class UGM;
class SocietyMenu;

enum class UserType {
    Unknown, Admin, Faculty, Student, SocietyMember, UniversityGeneral
};

class User : public Person {
protected:
    string username;
    string password;
    UserType role;

public:
    User();
    User(const string& username, const string& password, UserType role,
        const string& name, const string& gender, const string& dob,
        const string& email, const string& cnic, const string& contactNumber,
        const string& address);

    // Setters
    void setUsername(const string& username);
    void setPassword(const string& password);
    void setRole(UserType type);

    // Getters
    string getUsername() const;
    string getPassword() const;
    UserType getRole() const;

    static UserType stringToUserType(const string& s);
    static string userTypeToString(UserType t);

    // Serialization
    virtual void fromString(const string& data);
    virtual string toString() const;

    // Menu/logic (can be overridden in derived classes)
    virtual void showMenu();

    virtual ~User() {}
};

// Example derived classes if you want to extend for specific roles
class UniversityGeneralUser : public User /*, public UGM (if you have this interface) */ {
public:
    UniversityGeneralUser(const string& username, const string& password,
        const string& name, const string& gender, const string& dob,
        const string& email, const string& cnic, const string& contactNumber,
        const string& address);

    // Implement/override UGM interface methods if needed
};

class SocietyMemberUser : public User /*, public SocietyMenu (if you have this interface) */ {
public:
    SocietyMemberUser(const string& username, const string& password,
        const string& name, const string& gender, const string& dob,
        const string& email, const string& cnic, const string& contactNumber,
        const string& address);

    // Implement/override SocietyMenu interface methods if needed
};