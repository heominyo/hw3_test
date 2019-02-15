
add_source_problem(
    NAME stack
    USER_SOURCE ${HW_DIR}/ulliststr.cpp ${HW_DIR}/stackstring.cpp
    TEST_SOURCE stack_tests.cpp
    RUNTIME_TEST_SOURCE stack_runtime_tests.cpp)