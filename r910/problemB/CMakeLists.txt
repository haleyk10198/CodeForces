assemble_executable(problemB
        SOURCE main.cxx
        HEADERS main.hxx
        INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/common
)

add_executable(tests tests.cxx)
target_link_libraries(tests GTest::gtest GTest::gtest_main problemB)
gtest_discover_tests(tests)
