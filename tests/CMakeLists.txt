include(GoogleTest)

add_executable(linear-algebra linear_algebra.cpp)
target_link_libraries(linear-algebra PRIVATE oingo-math gtest pthread)

add_test(math-test linear-algebra)