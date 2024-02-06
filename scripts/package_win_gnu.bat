setlocal
@echo off

set "make_exe=make.exe"
set "cmake_exe=cmake.exe"

where %make_exe% > nul 2>&1
if %errorlevel% neq 0 (
    echo Please install make in your system.
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
%cmake_exe% ../ -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF

echo "Run make"
%make_exe%

echo "Run make package"
%make_exe% package

endlocal
@rem End of line.
@rem DO NOT WRITE BEYOND HERE.