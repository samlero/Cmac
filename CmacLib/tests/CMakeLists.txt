
if(BUILD_TESTING)
	add_executable(tests tests.cpp)
	target_link_libraries(tests PRIVATE GTest::gtest_main)
	include(GoogleTest)
	gtest_discover_tests(tests)
endif()