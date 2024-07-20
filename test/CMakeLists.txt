# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(stdlibTests LANGUAGES CXX)

# ---- Tests ----

add_executable(stdlib_test source/stdlib_test.cpp)
target_link_libraries(stdlib_test PRIVATE stdlib_lib)
target_compile_features(stdlib_test PRIVATE cxx_std_23)

add_test(NAME stdlib_test COMMAND stdlib_test)

# ---- End-of-file commands ----

add_folders(Test)
