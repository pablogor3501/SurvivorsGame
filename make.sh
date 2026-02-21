#!/bin/bash

# Load environment variables from .env file
if [ -f .env ]; then
  export $(grep -v '^#' .env | xargs)
fi

# Check if the build directory exists, if not, create it
if [ ! -d "$BUILD_DIR" ]; then
  echo "Build directory does not exist. Creating $BUILD_DIR..."
  mkdir -p "$BUILD_DIR"
fi

# Run cmake and make
cmake -S ./ -B $BUILD_DIR
make -C $BUILD_DIR
