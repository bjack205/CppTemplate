#include "gtest/gtest.h"

#include "foo.hpp"

TEST(TestSuiteName, TestName) {
  EXPECT_EQ(1, 2 - 1);
}

TEST(FooTests, Constructor) {
  foo::MyClass my_class;
  EXPECT_EQ(my_class.GetInt(), 0);
}