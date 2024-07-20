cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    stdlib
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    stdlib_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    stdlib_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(stdlib_lib PUBLIC cxx_std_23)

# ---- Declare executable ----

add_executable(stdlib_exe source/main.cpp)
add_executable(stdlib::exe ALIAS stdlib_exe)

set_property(TARGET stdlib_exe PROPERTY OUTPUT_NAME stdlib)

target_compile_features(stdlib_exe PRIVATE cxx_std_23)

target_link_libraries(stdlib_exe PRIVATE stdlib_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT stdlib_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of stdlib"
  )
endif()

include(cmake/dev-mode.cmake)
