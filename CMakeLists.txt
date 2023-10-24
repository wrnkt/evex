cmake_minimum_required(VERSION 3.21...3.27)

project(
    EVEX
    VERSION 0.1
    DESCRIPTION "Command line arithmetic expression parsing and evaluation."
    LANGUAGES C CXX
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
  build_boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.83.0
)
FetchContent_GetProperties( build_boost )
if( NOT build_boost_POPULATED )
    FetchContent_Populate(build_boost)
    add_subdirectory(
        ${build_boost_SOURCE_DIR}
        ${build_boost_BINARY_DIR}
        EXCLUDE_FROM_ALL
    )
endif()

add_subdirectory(src)
add_subdirectory(apps)
