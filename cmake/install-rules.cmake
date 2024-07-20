install(
    TARGETS stdlib_exe
    RUNTIME COMPONENT stdlib_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
