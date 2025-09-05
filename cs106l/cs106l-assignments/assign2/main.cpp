/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Chengxin Liao"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO: Implement this function.
  std::set<std::string> applicants;
  std::fstream file(filename);
  if (!file.is_open()){
    throw std::runtime_error("Unable to open file: " + filename);
  }

  std::string name;

  while(std::getline(file, name)){
    if (!name.empty()){
    applicants.insert(name);
    }
  }
  file.close();
  return applicants;

}

std::unordered_set<std::string> getApplicantNames(const std::string& filename) {
    std::unordered_set<std::string> applicants;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string name;
    while (std::getline(file, name)) {
        if (!name.empty()) {
            applicants.insert(name);
        }
    }

    file.close();
    return applicants;
}
/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // STUDENT TODO: Implement this function.
  std::queue<const std::string*> matches;
  std::string initials;
  if (!name.empty()){
    initials += name[0];
    //size_t means unsigned int 
    size_t space = name.find(" ");
    if (space != std::string::npos && space + 1 < name.length()){
      initials += name[space + 1];
    }
  }

  for (const std::string& student : students){
    std::string students_initials;
    if (!student.empty()){
      students_initials += student[0];
      size_t space = student.find(" ");
      if (space != std::string::npos && space + 1 < student.length()){
        students_initials += student[space + 1];
      }
    }
    if (students_initials == initials){
      matches.push(const_cast<std::string*>(&student));
    }
  }
  return matches;

}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // STUDENT TODO: Implement this function.
  if(matches.empty()){
    return "NO MATCHES FOUND";
  }

  const std::string* best_match= nullptr;
  int highest_score = -1;

  while(!matches.empty()){
    const std::string* current = matches.front();
    matches.pop();

    int score = current->length();
    if(current->find("love") != std::string::npos || current->find("Love") != std::string::npos){
      score += 10; 
    }

    if(score > highest_score){
      highest_score = score;
      best_match = current;
    }
    
  }
  return best_match ? *best_match : "NO MATCHES FOUND.";

}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
