#!/usr/bin/env bash

set -euo pipefail

# Build the automated test suite
mkdir -p build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/lib_coffee_machine
cmake --build . --config Release --target install -- -j $(nproc)

# Run the test
cd tests
export GTEST_COLOR=1
ctest --verbose
