#!/bin/bash
git submodule init
git submodule update
cmake -Bbuild -H.
cmake --build build --target all