#!/usr/bin/env bash

set -euo pipefail

# Build the automated test suite
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/tmp/lib_coffee_machine -DBUILD_TESTS=ON ..
cmake --build . --config Release -- -j $(nproc)
# Test installation target
cmake --build . --config Release --target install -- -j $(nproc)

# Run the test
cd tests
export GTEST_COLOR=1
ctest --verbose
