add_executable(evex evex.cpp)
target_compile_features(evex PRIVATE cxx_std_20)
target_link_libraries(evex PRIVATE evex_library)
target_link_libraries(evex PRIVATE util_library)
