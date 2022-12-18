# Function that adds a test executable for a source file with the name <testname>_test.cpp
# Adds an executable target of the name <testname>_test, and enables googletest on the target
#
# TIP: Add any other libraries you want to use for testing to the "target_link_libraries" command
# TIP: This is just for convenience, but is nice to avoid the boilerplate code when adding lots of test source files
function (unit_test testname)
  add_executable(${testname}_test ${testname}_test.cpp)
  target_link_libraries(${testname}_test PRIVATE gtest_main foo)  # add googletest as a dependency
  gtest_discover_tests(${testname}_test)                          # finds tests defined using googletest
endfunction()

# Adds the tests in `foo_test.cpp`
unit_test(foo)