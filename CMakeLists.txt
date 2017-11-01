cmake_minimum_required(VERSION 2.8)

# Locate GTest
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

#include_directories(
#    ${GTEST_INCLUDE_DIRS}
#    ${GMOCK_INCLUDE_DIRS}
#)

find_package(Threads REQUIRED)

# Needed to include the "ExternalProject" command
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# Download SystemC 2.3.2 (Cmake project) and compile
ExternalProject_Add(systemC_project
  URL http://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.2.tar.gz
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/systemc-2.3.2
  CMAKE_ARGS "${CMAKE_ARGS};-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
)
# Get external project installation directory
ExternalProject_Get_Property(systemC_project install_dir)


# Add include and lib directories
include_directories(${install_dir}/include)
LINK_DIRECTORIES(${install_dir}/lib)

# Add library
add_library(systemC SHARED IMPORTED)
set_property(TARGET systemC PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libsystemc.so)

# Download and install GTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)
# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)
# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")


# Adder build (With systemC dependency)
add_executable(adder adder.cpp)
add_dependencies(adder systemC_project)
target_link_libraries(adder systemC)

# Test build (With systemC dependency)
add_executable(test_play_systemc_types test_play_systemc_types.cpp)
add_dependencies(test_play_systemc_types systemC_project)
add_dependencies(test_play_systemc_types gtest)
target_link_libraries(test_play_systemc_types systemC libgtest Threads::Threads)

