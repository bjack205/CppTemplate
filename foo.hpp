//
// Created by Brian Jackson on 12/17/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#pragma once

#include <vector>

// TIP: Since this is included in the header file, it should be a PUBLIC dep,
//      since anything that includes this header will need the definitions of
//      the declarations in Eigen/Dense
//
//      NOTE: this is a little more subtle for header-only libraries like
//            Eigen, but it's a good rule to follow
#include "Eigen/Dense"

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
  // TIP: Use CamelCase for method names (per Google Style Guide)
  void Greet(int a);
  int GetInt();

  // TIP: Pass input arguments by "const reference", as shown here
  double ScaledInnerProduct(const std::vector<double> &a,
                            const std::vector<double> &b);

  /**
   * @brief Builds a vector of length \ref MyClass.GetInt(), filled with a constant value of @a value
   *
   * TIP: pass small data (like primitive types) by value
   *
   * @param value Value used to fill the vector
   * @return A vector filled with a constant value
   */
  Eigen::VectorXd BuildVector(double value);

  // TIP: Private methods and variables can only be accessed by the class itself
private:
  void PrintGreeting(int a);
  int b_; // TIP: use trailing underscore for private member variables
};

} // namespace foo