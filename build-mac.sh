#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

# generate CMake files
cmake -O . -B./build -DCMAKE_BUILD_TYPE=Debug -DBuild_SHARED_LIBS=ON

# copy assets & .dylib files to output dir
rsync -avz --delete "./Assets/" "./build/bin/Assets/"
rsync -avz --delete "./Mac/bin/" "./build/bin/Debug/"

# compile project
cd build && cmake --build .
echo Compilation Finished!

# run project
cd bin && ./Game
