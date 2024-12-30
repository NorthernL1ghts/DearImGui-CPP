@echo off
rem Create build directory if it doesn't exist
if not exist build (
    mkdir build
)

rem Navigate to build directory
cd build

rem Run CMake to generate project files
cmake -DCMAKE_INSTALL_PREFIX=../vendor ..

rem Build the project
cmake --build . --target install

rem Navigate back to the root directory
cd ..

@echo Project generation and build complete!
pause
