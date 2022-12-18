add_executable(foo_test foo_test.cpp)
target_link_libraries(foo_test PRIVATE gtest_main foo)
gtest_discover_tests(foo_test)