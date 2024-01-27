
if(BUILD_TESTING)
	add_executable(tests 
		CmacTests.cpp 
		FactoryTests.cpp 
		MarshallerTests.cpp 
		SerializableTests.cpp
		HelperTests.cpp)
	configure_file(expected.cmac expected_serialized.cmac COPYONLY)
	target_link_libraries(tests PRIVATE GTest::gtest_main)
	target_link_libraries(tests PRIVATE CmacLib)
	include(GoogleTest)
	gtest_discover_tests(tests)
	enable_testing()
endif()