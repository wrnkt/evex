add_executable(evex-v1 evex-v1.c)
target_compile_features(evex-v1 PRIVATE c_std_99)
target_link_libraries(evex-v1 PRIVATE evex_library)
target_link_libraries(evex-v1 PRIVATE util_library)
