#!/bin/sh

# Run this script from a posix compliant shell.

if ! command -v make > /dev/null 2>&1 ; then
    echo "Please install make in your system."
    exit -1
fi
if ! command -v cmake > /dev/null 2>&1 ; then
    echo "Please install cmake in your system."
    exit -1
fi

# The directory where this script exists.
script_dir="$(dirname "$(readlink -f "$0")")"

cd $script_dir/../
mkdir build
cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release
make
make package