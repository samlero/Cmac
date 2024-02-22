if (BUILD_TESTING)
    # Collect all files necessary for testing.
    file(GLOB_RECURSE julia_test_files
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.jl
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.jl
    )
    # Copy all test files to binary directory.
    foreach(test_jl_file ${julia_test_files})
        configure_file(
            ${test_jl_file}
            ${CMAKE_CURRENT_BINARY_DIR}
            COPYONLY
        )
    endforeach()

    find_program(JULIA_EXE julia)
    add_test(
        NAME JuliaWrapperTests
        COMMAND ${JULIA_EXE} runtests.jl
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()