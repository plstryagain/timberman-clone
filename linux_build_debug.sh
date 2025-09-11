#!/bin/bash

export SFML_ROOT=/home/maksim/Projects/lib/SFML-2.6.2

mkdir -p ./build
cd ./build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
cd ..
./build/timberman-clone