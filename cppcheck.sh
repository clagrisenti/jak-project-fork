#!/bin/bash
resFile="$(echo "$1" | tr / _).log"
echo $resFile
cppcheck --enable=all --language=c++ --std=c++20 $1 > cppcheck/$resFile
