assemble_executable(problemB
        SOURCE main.cxx
        HEADERS common/test-case.hxx common/int-math.hxx main.hxx
)

add_executable(tests tests.cxx)
target_link_libraries(tests GTest::gtest GTest::gtest_main problemB)
gtest_discover_tests(tests)
