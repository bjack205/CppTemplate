//
// Created by Brian Jackson on 12/17/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

namespace foo {

// TIP: Use CamelCase for class names
class MyClass {
  // TIP: Public methods and variables are accessible everywhere
public:
  // Constructors
  MyClass();
  MyClass(int b);

  // Destructor
  ~MyClass();

  // Methods
  void Greet(int a);
  int GetInt();

  // TIP: Private methods and variables can only be accessed by the class itself
private:
  void PrintGreeting(int a);
  int b_; // TIP: use trailing underscore for private member variables
};

}  // namespace foo