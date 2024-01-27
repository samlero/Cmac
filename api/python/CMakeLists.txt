project(CmacLibPythonWrapper)

if (NOT TARGET CmacLibPythonWrapper)
    find_package(pybind11)

    if (pybind11_FOUND)
        file(GLOB CmacLibPythonWrapperSrc
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        )
        add_library(
            CmacLibPythonWrapper ${CmacLibPythonWrapperSrc}
        )
        target_link_libraries(
            CmacLibPythonWrapper PRIVATE CmacLib PUBLIC pybind11::module
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
        # Add the Python module
        pybind11_add_module(cmaclib ${CmacLibPythonWrapperSrc})
        target_link_libraries(
            cmaclib PUBLIC CmacLibPythonWrapper
        )
    else()
        message("pybind11 is not installed in your system."
        " CmacLibPythonWrapper was not built")
    endif()
endif()