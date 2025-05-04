cmake_minimum_required(VERSION 3.25)

include( CPack )

project(hey VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(hey INTERFACE)

target_include_directories(hey INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:src>)

install(TARGETS hey
        EXPORT hey_targets
        INCLUDES DESTINATION include
)

install(DIRECTORY hey DESTINATION include)

install(EXPORT hey_targets
        FILE hey_targets.cmake
        NAMESPACE hey::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/hey
)

include(CMakePackageConfigHelpers)
configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/HeyConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/hey_config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/hey
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/hey_config_version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/hey_config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/hey_config_version.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/hey
)

add_subdirectory(tests)