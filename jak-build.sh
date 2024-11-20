#!/bin/bash

#dir=pwd
#cd $dir

buildModes=("Release")

for mode in ${buildModes[@]}; do

    buildDir="build"
    assert=""

    for var in "$@"; do
        if [ "$var" == "clean" ]; then
            echo "cleaning build"
            cmake --build $buildDir --target clean
        fi

        if [ "$var" == "no_assert" ]; then
            echo "disabling custom asserts"
            assert="-DCMAKE_CXX_FLAGS=\"-DNO_ASSERT=1\""
        fi
    done

    echo "building $mode"
    cmake -B $buildDir -DCMAKE_BUILD_TYPE=$mode $assert && cmake --build $buildDir -j 15

done
