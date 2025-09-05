#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
//default
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

//parameteric 
User::User(const std::string& name, const std::vector<std::string> friends)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0){
  for(const auto& friend_name:friends){
    add_friend(friend_name);
  }
}

//deconstruct
User::~User(){
  delete[] _friends;
}

//copy construct
User::User(const User& others)
  : _name(others._name)
  , _friends(others._capacity > 0 ? new std::string[others._capacity] : nullptr)
  , _size(others._size)
  , _capacity(others._capacity)
{
  for(size_t i = 0; i < _size; ++i){
    _friends[i] = others._friends[i];
  }
}

//copy assignment
User &User::operator=(const User& others){
  if(this != &others){
    std::string* new_friends = nullptr;
    if(others._capacity > 0){
      new_friends = new std::string[others._capacity];
      for(size_t i = 0; i < others._size; ++i){
        new_friends[i] = others._friends[i];
      }
    }
    delete[] _friends;
    
    _name = others._name;
    _friends = new_friends;
    _size = others._size;
    _capacity = others._capacity;
  }
  return *this;
}

User &User::operator+=(User& others){
  if(this != &others){
    add_friend(others._name);   
    others.add_friend(this->_name);
  }
  return *this;
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
  void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */

std::ostream& operator<<(std::ostream& os, const User& user){
  os << "User(name=" << user.get_name() << ", friends=[";
  for(size_t i=0; i < user.size(); i++){
    if(i != 0){
    os << ", ";
    }
    os << user._friends[i];
  }

  os << "])";
  return os;
}

bool User::operator<(const User& others) const{
    return _name < others._name;
}
