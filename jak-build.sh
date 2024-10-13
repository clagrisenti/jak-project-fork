#!/bin/bash

#dir=pwd
#cd $dir

buildModes=("Release")

for mode in ${buildModes[@]}; do

    buildDir="build"
    cmake -B $buildDir -DCMAKE_BUILD_TYPE=$mode && cmake --build $buildDir -j 13

done
