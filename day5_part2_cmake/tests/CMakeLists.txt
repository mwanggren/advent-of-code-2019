add_executable(tests test.cpp)

target_include_directories(tests PRIVATE ../include)
target_include_directories(tests PRIVATE ../external)

target_link_libraries(tests PRIVATE computer)

target_compile_features(tests PRIVATE cxx_std_17)
set_target_properties(tests PROPERTIES 
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS OFF)
target_compile_options(tests PRIVATE -Werror -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion)

add_test(NAME tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND tests)
