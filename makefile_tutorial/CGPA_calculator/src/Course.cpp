#include "Course.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <map>
#include <algorithm>

bool CGPACalculator::loadCoursesFromFile(const std::string& filename){
  std::ifstream fin(filename);
  if (!fin.is_open()){
    return false;
  }

  Course c;
  while (fin >> c.code >> c.credits >> c.grade){
    courses.push_back(c);
  }
  fin.close();
  return true;
}

void CGPACalculator::inputCoursesFromConsole(){
  int n;
  std::cout << "Please Enter number of Courses:";
  std::cin >> n;
  for (int i = 0; i < n; i++){
    Course c;
    std::cout << "Course" << i+1 << "Code,Credits,grade";
    std::cin >> c.code >> c.credits >> c.grade;
    courses.push_back(c);
  }
}

void CGPACalculator::addCourse(const Course& c) {
    courses.push_back(c);
}

void CGPACalculator::sortCourses(){
  std::sort(courses.begin(), courses.end(),
      [](const Course& a, const Course& b){
        return a.code < b.code;
      });
}

double CGPACalculator::gradeToPoint(const std::string& grade) const{
   bool isNumeric = !grade.empty() &&
      std::all_of(grade.begin(), grade.end(), [](char c) {
          return std::isdigit(c) || c == '.';
      }); 
   if (isNumeric){
     double presentage;
     std::istringstream(grade) >> presentage;

     if (presentage < 0.0) presentage = 0.0;
     if (presentage > 100.0) presentage = 100.0;

     if (presentage < 60.0) 
       return 0.0;
     else 
       return 1.0 + (presentage - 60.0)/40.0 * 4.0; 
   } else {
   return 0.0; 
   }
}

void CGPACalculator::displayCourses() const{
  std::cout << std::left 
    << std::setw(12) << "Course Code" 
    << std::setw(8) << "Course credits"
    << std::setw(8) << "Course grade"
    << "\n";

  std::cout << "-------------------------------------------------\n";
  
  for (const auto& cr: courses){
  std::cout << std::left 
    << std::setw(12) << cr.code 
    << std::setw(8) << cr.credits 
    << std::setw(8) << cr.grade 
    << "\n";
  }
} 

double CGPACalculator::computeAndDisplayCGPA() const{
  double totalCredits = 0.0;
  double totalGrade = 0.0;
  double gpa = 0.0;
  for (const auto& cr : courses){
    totalCredits += cr.credits; 
    totalGrade += cr.credits * gradeToPoint(cr.grade); 
  }
  gpa = totalGrade / totalCredits;

  std::cout << "\nTotalCredits" << totalCredits
            << "\nGPA/CGPA" << std::fixed << std::setprecision(2) << gpa
            << "\n";
  return gpa;
}

const std::vector<Course>& CGPACalculator::getCourses() const {
    return courses;
}
