//
// Created by Brian Jackson on 12/17/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "foo.hpp"

#include "fmt/core.h"

namespace foo {

MyClass::MyClass() : b_(0) {}
MyClass::MyClass(int b) : b_(b) {}
MyClass::~MyClass() {}

int MyClass::GetInt() { return b_; }

void MyClass::Greet(int a) { PrintGreeting(a); }
void MyClass::PrintGreeting(int a) {
  fmt::print("Hello from MyClass! a = {}, b = {}\n", a, b_);
}

}  // namespace foo