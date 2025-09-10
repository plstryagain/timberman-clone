#!/bin/bash

export SFML_ROOT=/Users/maksim/Documents/Projects/libs/sfml-2.6.2

mkdir -p ./build
cd ./build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
cd ..
./build/timberman-clone