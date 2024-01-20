cd ..
echo "Make build directory"
mkdir build
cd build

echo "Run CMake on core"
cmake ../core/ -G "Unix Makefiles"

echo "Run make"
make

echo "Run make package"
make package


