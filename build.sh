#!/bin/bash

if [[ -e "build" ]]; then
    rm build -rf
fi

mkdir build
cd build
cmake ..
make
make package
