
if(BUILD_TESTING)
	add_executable(tests 
		CmacTests.cpp 
		FactoryTests.cpp 
		MarshallerTests.cpp 
		SerializableTests.cpp
		HelperTests.cpp)
	target_link_libraries(tests PRIVATE GTest::gtest_main)
	target_link_libraries(tests PRIVATE CmacLib)
	include(GoogleTest)
	gtest_discover_tests(tests)
	enable_testing()
endif()