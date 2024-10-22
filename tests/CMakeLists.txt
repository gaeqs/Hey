find_package(Catch2 REQUIRED)

include(CTest)
include(Catch)

project(hey_tests)
set(CMAKE_CXX_STANDARD 20)

add_executable(hey_tests basic.cpp examples.cpp)
target_link_libraries(hey_tests PUBLIC hey Catch2::Catch2WithMain)

catch_discover_tests(hey_tests)

project(hey_tests_pointer)
set(CMAKE_CXX_STANDARD 20)

add_executable(hey_tests_pointer pointer.cpp)
target_link_libraries(hey_tests_pointer PUBLIC hey Catch2::Catch2WithMain)

catch_discover_tests(hey_tests_pointer)