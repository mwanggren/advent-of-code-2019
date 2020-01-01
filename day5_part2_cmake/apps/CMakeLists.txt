add_executable(app app.cpp)

target_include_directories(app PRIVATE ../include)

target_link_libraries(app PRIVATE computer)

target_compile_features(app PRIVATE cxx_std_17)
set_target_properties(app PROPERTIES 
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS OFF)
target_compile_options(app PRIVATE -Werror -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion)
