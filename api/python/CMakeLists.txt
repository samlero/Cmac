project(CmacLibPythonWrapper)

if (NOT TARGET CmacLibPythonWrapper)
    find_package(pybind11)
    find_package(Python)

    if (pybind11_FOUND)
        file(GLOB CmacLibPythonWrapperSrc
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/../../core/src/*.cpp
        )
        add_library(
            CmacLibPythonWrapper SHARED ${CmacLibPythonWrapperSrc}
        )
        target_link_libraries(
            CmacLibPythonWrapper PRIVATE pybind11::module
        )
        set_target_properties(CmacLibPythonWrapper PROPERTIES
            PREFIX "${PYTHON_MODULE_PREFIX}"
            SUFFIX "${PYTHON_MODULE_EXTENSION}"
        )
        # Access implementation classes.
        target_include_directories(
            CmacLibPythonWrapper PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/../../core/include
            ${CMAKE_CURRENT_SOURCE_DIR}/../../core/include_internal
        )
        set_property(
            TARGET CmacLibPythonWrapper
            PROPERTY CMAKE_POSITION_INDEPENDENT_CODE ON
        )
        # Add the Python module
        pybind11_add_module(cmaclib ${CmacLibPythonWrapperSrc})
        target_link_libraries(
            cmaclib PUBLIC CmacLibPythonWrapper
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
            find_program(PYTHON_EXE python)
            add_test(
                NAME PythonWrapperTests
                COMMAND ${PYTHON_EXE} -m pytest
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )
        endif()
    else()
        message("pybind11 is not installed in your system."
        " CmacLibPythonWrapper was not built")
    endif()
endif()