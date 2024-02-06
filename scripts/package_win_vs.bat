setlocal
@echo off

set "msbuild_exe=msbuild.exe"
set "cmake_exe=cmake.exe"

where %msbuild_exe% > nul 2>&1
if %errorlevel% neq 0 (
    echo Please install msbuild in your system.
    exit /b 1
)
where %cmake_exe% > nul 2>&1
if %errorlevel% neq 0 (
    echo Please install cmake in your system.
    exit /b 1
)

@rem The directory where this script exists.
set "script_dir=%~dp0"

cd %script_dir%\..
echo "Make build directory"
mkdir build
cd build

echo "Run CMake on core"
%cmake_exe% ../core/ -DCMAKE_BUILD_TYPE=Release

echo "Run PACKAGE.vcxproj"
%msbuild_exe% PACKAGE.vcxproj /property:Configuration=Release

endlocal
@rem End of line.
@rem DO NOT WRITE BEYOND HERE.