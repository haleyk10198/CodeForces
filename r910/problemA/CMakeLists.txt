assemble_executable(problemA
        SOURCE problemA.cpp
        HEADERS problemA.hxx common/test-case.hxx
)

target_add_cf_options(problemA_flattened)
