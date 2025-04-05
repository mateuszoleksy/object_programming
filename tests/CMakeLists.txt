enable_testing()

add_executable(unit_tests
        test_client.cpp
)

target_link_libraries(unit_tests
        GTest::GTest
        GTest::GMock
        pthread
)

add_test(NAME ClientTests COMMAND unit_tests)