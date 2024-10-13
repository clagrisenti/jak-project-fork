#!/bin/bash

find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\|c\|h\|frag\|vert\)' \
        -exec clang-format -style=file -i {} \;
