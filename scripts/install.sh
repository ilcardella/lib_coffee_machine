#!/usr/bin/env bash

set -euo pipefail

# Build the automated test suite
mkdir -p build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/usr/local/lib
cmake --build . --config Release --target install -- -j $(nproc)
