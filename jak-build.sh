#!/bin/bash

#dir=pwd
#cd $dir

buildModes=("Release")

for mode in ${buildModes[@]}; do

    buildDir="build"

    if [ "$1" == "clean" ]; then
        echo "cleaning build"
        cmake --build $buildDir --target clean
    fi

    echo "building $mode"
    cmake -B $buildDir -DCMAKE_BUILD_TYPE=$mode && cmake --build $buildDir -j 13

done
