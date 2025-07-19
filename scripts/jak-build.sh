#!/bin/bash

buildModes=("Release")

buildDir="build"
processes_used=$(($(nproc --all)))
#flags="-DCMAKE_CXX_FLAGS=\"-DNO_LOG=1 -DNO_ASSERT=1\""
        #-DCMAKE_CXX_FLAGS="-DNO_LOG=1-DNO_ASSERT=1" \

echo $flags

for mode in ${buildModes[@]}; do

    echo "building $mode"
    echo "processes $processes_used"

    cmake \
        -B $buildDir \
        -DCMAKE_BUILD_TYPE=$mode \
        -DCMAKE_CXX_FLAGS="-D__AVX2__=1 -DNO_LOG=1 -DNO_ASSERT=1" \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
        -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld" \
        -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ &&
        cmake \
            --build $buildDir \
            -j $processes_used
done

