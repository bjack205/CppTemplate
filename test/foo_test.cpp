#include "gtest/gtest.h"

#include <vector>

#include "foo.hpp"

TEST(TestSuiteName, TestName) {
  EXPECT_EQ(1, 2 - 1);
}

TEST(FooTests, Constructor) {
  foo::MyClass my_class;
  EXPECT_EQ(my_class.GetInt(), 0);
}

TEST(FooTests, InnerProduct) {
  std::vector<double> a = {0, 1, 2, 3};
  std::vector<double> b = {1, 2, 3, 4};
  foo::MyClass my_class(2);
  double dot = my_class.ScaledInnerProduct(a, b);
  EXPECT_DOUBLE_EQ(dot, 2 * (2 + 6 + 12));
}

TEST(FooTests, BuildVector) {
  int len = 2;
  foo::MyClass my_class(len);
  // TIP: You can use the "auto" return type to let the compiler figure out the return type
  //      It's useful, but many people suggest using it sparingly, since it make the code less clear
  //      I personally use it when the return type is too verbose, or unimportant for code clarity
  //      For example, I'd probably not use "auto" here, but use it as an example
  double value = 10;
  auto vec = my_class.BuildVector(value);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_DOUBLE_EQ(vec(0), value);
  EXPECT_DOUBLE_EQ(vec[0], value);  // for vectors, you can use either [] or () indexing
  EXPECT_DOUBLE_EQ(vec.sum(), value * len);
  EXPECT_TRUE(vec.isApprox(Eigen::VectorXd::Constant(len, value)));
}