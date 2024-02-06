# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.13)
project(CmacLib)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW) 
endif()

## <region> Enforcing C++ standards.
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
## Enforcing C and C++ standards. </region>

include(CTest)

add_subdirectory(core)

find_package(GTest)
# Prioritize using installed library.
if (NOT GTest_FOUND)
  # Only include this directory if gtest lib not installed in the system.
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)
endif()

add_subdirectory(tests)
add_subdirectory(api/python)