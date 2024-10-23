#!/bin/bash

#dir=pwd
#cd $dir

buildModes=("Release")

for mode in ${buildModes[@]}; do

    echo "building $mode"

    buildDir="build"
    
    if [ "$1" == "clean" ]; then
        cmake --build $buildDir --target clean
    fi
    
    cmake -B $buildDir -DCMAKE_BUILD_TYPE=$mode && cmake --build $buildDir -j 13

done
