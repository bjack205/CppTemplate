#include "foo.hpp"
#include "fmt/core.h"

void GreetWorld() {
  fmt::print("Hello, world!\n");
}

int main() {
  // Construct classes
  foo::MyClass my_class_1;
  foo::MyClass my_class_2(20);

  // Call member functions
  my_class_1.Greet(10);
  my_class_2.Greet(30);

  // Call local method
  GreetWorld();
  return 0;
}