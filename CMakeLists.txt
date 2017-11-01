cmake_minimum_required(VERSION 2.8)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)

# Needed to include the "ExternalProject" command
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# Download SystemC 2.3.2 (Cmake project) and compile
ExternalProject_Add(systemC_project
  URL http://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.2.tar.gz
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

# Adder build (With systemC dependency)
add_executable(adder adder.cpp)
add_dependencies(adder systemC_project)
target_link_libraries(adder systemC)

