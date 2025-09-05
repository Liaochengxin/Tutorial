#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

struct Course {
  std::string code;
  double credits;
  //std::string lecturer;
  std::string grade;
};

class CGPACalculator {
public:
  //automatic
  bool loadCoursesFromFile(const std::string& filename);
  //manual
  void inputCoursesFromConsole(); 
  void addCourse(const Course& c);
  void sortCourses();
  void displayCourses() const;
  double computeAndDisplayCGPA() const;
  const std::vector<Course>& getCourses() const;
  double gradeToPoint(const std::string& grade) const;
  
private:
  std::vector<Course> courses;
};

#endif //Course.h
