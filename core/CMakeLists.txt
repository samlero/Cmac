cmake_minimum_required (VERSION 3.13)

## <region> Enforcing C++ standards.
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
## Enforcing C and C++ standards. </region>

project ("CmacLib")

add_library (CmacLib STATIC)

file(GLOB SOURCES "src/*.cpp")
file(GLOB INTERNAL_INCLUDE "include_internal/*.h")


target_sources(${PROJECT_NAME}
    PRIVATE
        ${SOURCES} 
        ${INTERNAL_INCLUDE})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/include_internal
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS CmacLib LIBRARY DESTINATION bin)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION "include")

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A Cerebellar Model Articulation Controller (CMAC) library in the context of control systems.")
SET(CPACK_PACKAGE_VENDOR "samlero & aldhinn")

SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "004")
SET(CPACK_PACKAGE_VERSION_PATCH "0")

SET(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})

set (CPACK_RESOURCE_FILE_LICENSE
     "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE")

include(CPack)