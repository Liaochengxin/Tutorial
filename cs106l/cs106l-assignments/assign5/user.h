/*
 * CS106L Assignment 5: TreeBook
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include <iostream>
#include <string>

class User
{
public:
  //default constructor
  User(const std::string& name);
  User(const std::string& name, const std::vector<std::string> friends);

  //deconstructor
  ~User();

  //copy constructor
  User(const User& others);
  //copy assignment
  User& operator=(const User& others);

  //move constructor
  User(const User&&) = delete;

  //move assignment
  User& operator=(const User&&) = delete;

  User& operator+=(User& others);

  void add_friend(const std::string& name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string& name);


  friend std::ostream& operator<<(std::ostream& os, const User& user);
  bool operator<(const User& others) const;
  /** 
   * STUDENT TODO:
   * Your custom operators and special member functions will go here!
   */

private:
  std::string _name;
  std::string* _friends;
  size_t _size;
  size_t _capacity;
};
