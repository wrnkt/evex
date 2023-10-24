# headers must be listed in add_library to show up in IDEs
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${EVEX_SOURCE_DIR}/include/evex/*.hpp")

add_library(evex_library
    util.cpp
    ${HEADER_LIST}
)

target_include_directories(evex_library PUBLIC ../include)
target_link_libraries(evex_library PRIVATE Boost::program_options)
target_compile_features(evex_library PUBLIC cxx_std_20)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)
