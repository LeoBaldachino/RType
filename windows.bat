@echo off
setlocal

cls

if exist boost (
   echo "Boost library found."
) else (
    echo "Boost library not found. Installing submodules..."
    git submodule update --init --recursive
)

cd boost
b2.exe headers

cd ..
mkdir build
cd build
cmake ..