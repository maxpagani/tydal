find_package( GTest REQUIRED )
include( GoogleTest )

add_executable( tydal_tests
    Test_ComplexTypes.cc
    Test_CreateParser.cc
    Test_NestedTypes.cc
    Test_ParseErrors.cc
    Test_RecordScala.cc
    Test_SimpleScala.cc
)
target_link_libraries( tydal_tests PRIVATE tydal_core GTest::gtest_main )

# the timeout turns a parser that stops consuming input into a failure
gtest_discover_tests( tydal_tests PROPERTIES TIMEOUT 10 )
