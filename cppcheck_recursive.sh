#!/bin/bash

find "$(pwd -P)" -regex '.*\.\(cpp\|hpp\|cc\|cxx\|c\|h\|frag\|vert\)' \
       -exec bash cppcheck.sh {} \; 
