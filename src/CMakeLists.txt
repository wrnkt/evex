# headers must be listed in add_library to show up in IDEs

file(GLOB EVEX_HEADER_LIST CONFIGURE_DEPENDS "${EVEX_SOURCE_DIR}/include/evex/*.hpp")
add_library(evex_library
    tokenizer.cpp
    ${EVEX_HEADER_LIST}
)
target_include_directories(evex_library PUBLIC ../include)
target_link_libraries(evex_library PRIVATE Boost::program_options)
target_compile_features(evex_library PUBLIC cxx_std_20)


file( GLOB UTIL_HEADER_LIST CONFIGURE_DEPENDS "${EVEX_SOURCE_DIR}/include/util/*.hpp" )
add_library(util_library
    util.cpp
    ${UTIL_HEADER_LIST}
)
target_include_directories( util_library PUBLIC ../include )
target_compile_features( util_library PUBLIC cxx_std_20 )


source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${EVEX_HEADER_LIST} ${UTIL_HEADER_LIST}
)
