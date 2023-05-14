cmake_minimum_required(VERSION 3.18)

project (oingo VERSION 1.0 LANGUAGES CXX)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_subdirectory(apps)
add_subdirectory(tests)
add_subdirectory(src)
