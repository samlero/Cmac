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
            CmacLibPythonWrapper PRIVATE CmacLib pybind11::module
        )
        set_target_properties(CmacLibPythonWrapper PROPERTIES
            PREFIX "${PYTHON_MODULE_PREFIX}"
            SUFFIX "${PYTHON_MODULE_EXTENSION}"
        )
        target_include_directories(
            CmacLibPythonWrapper PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
    else()
        message("pybind11 is not installed in your system."
        " CmacLibPythonWrapper was not built")
    endif()
endif()