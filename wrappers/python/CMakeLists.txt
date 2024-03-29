project(CmacLibPythonWrapper)

if (NOT DEFINED cmaclib_src)
    find_package(pybind11)
    find_package(Python)

    if (pybind11_FOUND)
        file(GLOB cmaclib_src
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        )
        # Add the Python module
        pybind11_add_module(pycmaclib ${cmaclib_src})
        target_link_libraries(
            pycmaclib PRIVATE CmacLibD pybind11::module
        )
        set_target_properties(pycmaclib PROPERTIES
            PREFIX "${PYTHON_MODULE_PREFIX}"
            SUFFIX "${PYTHON_MODULE_EXTENSION}"
        )
        set_property(TARGET pycmaclib PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

        # Testing.
        if (BUILD_TESTING AND NOT Python_FOUND)
            message("Cannot do testing since python is not installed.")
        elseif(BUILD_TESTING AND Python_FOUND)
            # Collect all test files.
            file(GLOB_RECURSE python_test_files
                ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.py
                ${CMAKE_CURRENT_SOURCE_DIR}/src/*.pyi
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
                COMMAND ${PYTHON_EXE} -m pytest -s
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )
        endif()

        install(TARGETS pycmaclib LIBRARY DESTINATION lib)
        install(FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/src/pycmaclib.pyi
            DESTINATION lib
        )
    else()
        message("pybind11 is not installed in your system."
        " CmacLibPythonWrapper was not built")
    endif()
endif()