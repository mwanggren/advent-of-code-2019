add_library(computer Computer.cpp)

target_include_directories(computer PUBLIC ../include)

target_compile_features(computer PRIVATE cxx_std_17)
set_target_properties(computer PROPERTIES 
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS OFF)
target_compile_options(computer PRIVATE -Werror -Wall -Wextra -pedantic-errors)
#  -Wconversion -Wsign-conversion
