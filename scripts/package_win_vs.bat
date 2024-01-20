cd ..
echo "Make build directory"
mkdir build
cd build

echo "Run CMake on core"
cmake ../core/

echo "Run PACKAGE.vcxproj"
msbuild PACKAGE.vcxproj /property:Configuration=Release


