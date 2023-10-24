cmake_minimum_required(VERSION 3.21...3.27)

project(
    EVEX
    VERSION 0.1
    DESCRIPTION "Command line arithmetic expression parsing and evaluation."
    LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 20)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#     find_package(Doxygen)
#     if(DOXYGEN_FOUND)
#         add_subdirectory(docs)
#     else()
#         message(STATUS "Doxygen not found. Not building Docs.")
#     endif()
endif()

include(FetchContent)

set(BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.83.0
)

FetchContent_MakeAvailable( Boost )

add_subdirectory(src)
add_subdirectory(apps)
