cmake_minimum_required(VERSION 3.16)

project(Day7Part1 LANGUAGES CXX)

add_compile_options(-fsanitize=address,undefined)
# The following should not be needed? I need it on MacOS...
add_link_options(-fsanitize=address,undefined)

add_subdirectory(src)
add_subdirectory(apps)
enable_testing()
add_subdirectory(tests)