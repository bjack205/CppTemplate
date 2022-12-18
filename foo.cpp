//
// Created by Brian Jackson on 12/17/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "foo.hpp"

// TIP: Since fmt is only used in the .cpp files, it should be a PRIVATE dep
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
double MyClass::ScaledInnerProduct(const std::vector<double> &a,
                                   const std::vector<double> &b) {
  int len = std::min(a.size(), b.size());
  double value = 0;
  for (int i = 0; i < len; ++i) {
    value += a[i] * b[i];
  }
  return value * b_;
}

Eigen::VectorXd MyClass::BuildVector(double value) {
  // TIP: You can reference the current class using the `this` pointer. Use when you want to clearly
  //      show that the data is coming from the class.
  int vec_length = this->b_;

  // Create a vector using Eigen
  Eigen::VectorXd vec = Eigen::VectorXd::Constant(vec_length, value);
  return vec;
}

} // namespace foo