project(CmacLibPythonWrapper)

if (NOT DEFINED CmacLibPythonWrapperSrc)
    find_package(pybind11)
    find_package(Python)

    if (pybind11_FOUND)
        file(GLOB CmacLibPythonWrapperSrc
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        )
        # Add the Python module
        pybind11_add_module(cmaclib ${CmacLibPythonWrapperSrc})
        target_link_libraries(
            cmaclib PRIVATE CmacLib pybind11::module
        )
        set_target_properties(cmaclib PROPERTIES
            PREFIX "${PYTHON_MODULE_PREFIX}"
            SUFFIX "${PYTHON_MODULE_EXTENSION}"
        )
        # Access implementation classes.
        target_include_directories(
            cmaclib PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/../../core/include
            ${CMAKE_CURRENT_SOURCE_DIR}/../../core/include_internal
        )

        # Testing.
        if (BUILD_TESTING AND NOT Python_FOUND)
            message("Cannot do testing since python is not installed.")
        elseif(BUILD_TESTING AND Python_FOUND)
            # Collect all test files.
            file(GLOB_RECURSE python_test_files
                ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.py
            )
            # Copy all test files to binary directory.
            foreach(test_py_file ${python_test_files})
                configure_file(
                    ${test_py_file}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    COPYONLY
                )
            endforeach()
            find_program(PYTEST_EXE pytest)
            add_test(
                NAME PythonWrapperTests
                COMMAND ${PYTEST_EXE} -s
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )
        endif()
    else()
        message("pybind11 is not installed in your system."
        " CmacLibPythonWrapper was not built")
    endif()
endif()