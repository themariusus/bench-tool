#!/bin/bash

#-Wall - generate all warnings
#-Werror - warnings as errors
#-g - gdb debug symbols
#-O - optimize

gcc -g -Wall -Werror -lstdc++ ../src/main.cpp -o ../build/main
