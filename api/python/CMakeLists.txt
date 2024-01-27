project(CmacLibPythonWrapper)

if (NOT DEFINED CmacLibPythonWrapperSrc)
    find_package(pybind11)

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
    else()
        message("pybind11 is not installed in your system."
        " CmacLibPythonWrapper was not built")
    endif()
endif()