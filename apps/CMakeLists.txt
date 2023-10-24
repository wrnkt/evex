add_executable(evex evex.c)
target_compile_features(evex PRIVATE c_std_99)
target_link_libraries(evex PRIVATE evex_library)

add_executable(hello hello.cpp)
target_compile_features(hello PRIVATE cxx_std_20)
target_link_libraries(hello PRIVATE evex_library)
