# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(stdlibTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(GTest REQUIRED)
include(GoogleTest)

# ---- Tests ----

add_executable(stdlib_test
  src/memory/unique_ptr.cpp
)

target_link_libraries(stdlib_test PRIVATE stdlib_lib)
target_link_libraries(
  stdlib_test PRIVATE
  stdlib_lib
  GTest::gtest_main
)
target_compile_features(stdlib_test PRIVATE cxx_std_23)


# ---- End-of-file commands ----

gtest_discover_tests(stdlib_test)
add_folders(Test)
