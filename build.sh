#!/bin/bash

CXX=${CXX:-g++}
CXXFLAGS=${CXXFLAGS:-"-O2 -ldl -lGL -lglfw"}
SOURCE="main.cpp glad/glad.c shaders/shader.cpp window/window.cpp"
OUTPUT="mandelbrot"
echo "Compiling..."
$CXX $CXXFLAGS $SOURCE -o $OUTPUT
if [ $? -eq 0 ]; then
  echo "Compilation successful."
  echo "Running $OUTPUT..."
  ./"$OUTPUT"
else
  echo "Compilation failed."
  exit 1
fi
