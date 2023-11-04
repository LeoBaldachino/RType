@echo off
setlocal enabledelayedexpansion
cls
echo "Starting the build process..."
echo "Please wait..."

if exist boost (
   echo "Boost library found."
) else (
    echo "Boost library not found. Installing submodules..."
    git submodule update --init --recursive >nul 2>&1
    echo "Submodules installed."
)

echo "Setting up Boost headers..."
cd boost
call :spinner >nul 2>&1
b2.exe headers >nul 2>&1
echo "Boost headers set up."

cd ..
echo "Cleaning up old build files..."
if exist build (
   rmdir /s /q build >nul 2>&1
)
echo "Old build files cleaned up."

echo "Creating new build directory..."
mkdir build >nul 2>&1
cd build
echo "New build directory created."

echo "Running cmake..."
call :spinner >nul 2>&1
cmake .. >nul 2>&1
echo "Cmake run successfully."
