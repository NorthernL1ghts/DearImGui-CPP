#!/bin/bash

# Navigate to the root directory
cd ..

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Navigate to build directory
cd build

# Run CMake to generate project files
cmake -DCMAKE_INSTALL_PREFIX=../vendor ..

# Build the project
cmake --build . --target install

# Navigate back to the root directory
cd ..

echo "Project generation and build complete!"
