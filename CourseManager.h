#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
class CoursesManager {
public:
    CoursesManager();
    ~CoursesManager();

    void showMenu();

    // Core operations
    void addCourse();
    void assignCourseToFaculty();
    void enrollStudentInCourse();
    void viewCourses() const;

private:
    vector<map<string, string>> loadCourses() const;
    void saveCourses(const vector<map<string, string>>& courses) const;
    int findCourseIndexById(const vector<map<string, string>>& courses, const string& courseId) const;
    void showError(const string& message) const;
};