#!/bin/bash

CC="clang++"
CCFLAGS="-std=c++11 -Wall -Wextra"
EXE="main"
SRC="*.cpp"

$CC $CCFLAGS $SRC -o $EXE
