#!/bin/bash

set -e 

CXX=clang++

SRC="src/main.cpp src/physics/physics-engine.cpp  src/game-loop/game-loop.cpp"

OUT="wizards-nest"

CXXFLAGS="-std=c++17 -Wall -Wextra -O2"

LIBS="-lraylib -lGL -lm -lpthread -ldl -lrt -lX11"

echo "Building..."

$CXX $SRC $CXXFLAGS $INCLUDE_PATHS $LIBRARY_PATHS $LIBS -o $OUT

echo "Build successful."

