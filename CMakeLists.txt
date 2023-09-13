cmake_minimum_required(VERSION 3.13.2)
project(picosim VERSION 0.0.1 DESCRIPTION "Simulator of RP2040 microcontroller")

#--------------------------------------------------------------
# Options
#
cmake_policy(SET CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
cmake_policy(SET CMP0077 NEW)
set(CMAKE_MACOSX_RPATH ON)

# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# the RPATH to be used when installing
set(CMAKE_INSTALL_RPATH "")

# don't add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#--------------------------------------------------------------
# C++ flags
#
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#--------------------------------------------------------------
# Configure clang-tidy
#
option(CLANG_TIDY "Use clang-tidy if available" OFF)
option(CLANG_TIDY_FIX "Perform fixes for Clang-Tidy" OFF)
find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
)

# Find path of run-clang-tidy.py script.
file(GLOB CLANG_SHARE
    /usr/local/Cellar/llvm/10.*/share/clang
    /usr/lib/llvm-10/share/clang
)
find_program(
    RUN_CLANG_TIDY_PY
    NAMES "run-clang-tidy.py"
    PATHS ${CLANG_SHARE}
    DOC "Path to clang-tidy executable"
)

if(CLANG_TIDY)
    if(CLANG_TIDY_EXE)
        if(CLANG_TIDY_FIX)
            set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "-fix")
        else()
            set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
        endif()
    endif()
endif()

add_custom_target(check
    COMMAND cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
    COMMAND ${RUN_CLANG_TIDY_PY} -header-filter='.*' -checks='clang-analyzer-*' -quiet
    COMMENT "Generating code issues!"
)

#--------------------------------------------------------------
# GoogleTest
#
include(FetchContent)
include(ExternalProject)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
set(BUILD_SHARED_LIBS ON)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    set(BUILD_GMOCK OFF)
    set(INSTALL_GTEST OFF)
endif()

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

include(GoogleTest)
enable_testing()
get_target_property(GTEST_INCLUDE_DIR gtest INCLUDE_DIRECTORIES)
include_directories(simulator ${GTEST_INCLUDE_DIR})
set_target_properties(gtest PROPERTIES DEBUG_POSTFIX "")
set_target_properties(gtest_main PROPERTIES DEBUG_POSTFIX "")

#--------------------------------------------------------------
# Subdirectories
#
add_subdirectory(src)
add_subdirectory(test)
