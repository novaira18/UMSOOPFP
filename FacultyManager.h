#pragma once

#include <string>
#include <vector>
#include <map>

// Forward declaration for file utility functions
class FacultyManager {
public:
    FacultyManager();
    ~FacultyManager();

    void showMenu();

    // Core operations
    void addFaculty();
    void viewFaculties() const;
    void editFaculty();
    void deleteFaculty();

private:
    // Helper methods
    std::vector<std::map<std::string, std::string>> loadFaculties() const;
    void saveFaculties(const std::vector<std::map<std::string, std::string>>& faculties) const;
    int findFacultyIndexById(const std::vector<std::map<std::string, std::string>>& faculties, const std::string& facultyId) const;
    void showError(const std::string& message) const;
};