#include "user.h"
#include <cassert>
#include <iostream>
#include <sstream>

void test_output_function(){
  User user("Amy", {"Bob", "Alice"});
  std::ostringstream oss;
  oss << user;
  std::string result = oss.str();
  std::cout << result << std::endl;
}

int main(){
  test_output_function();
}
