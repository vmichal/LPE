#!/bin/bash

rm -rf build
mkdir -p build

cd build
cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake ..
ninja

