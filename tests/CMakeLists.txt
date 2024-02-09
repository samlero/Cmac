
if(BUILD_TESTING)
	add_executable(tests 
		CmacTests.cpp 
		FactoryTests.cpp 
		MarshallerTests.cpp 
		SerializableTests.cpp
		HelperTests.cpp)
	target_link_libraries(tests PRIVATE GTest::gtest_main)
	target_link_libraries(tests PRIVATE CmacLib)
	# Including internal headers to test helpers.
	target_include_directories(
		tests PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../core/include_internal
	)
	include(GoogleTest)
	gtest_discover_tests(tests)
	enable_testing()
endif()