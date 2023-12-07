assemble_executable(problemD
        SOURCE main.cxx
        HEADERS main.hxx
        INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/common
)

#add_executable(problemD_test tests.cxx)
#target_link_libraries(problemD_test GTest::gtest GTest::gtest_main problemD)
#gtest_discover_tests(problemD_test)
