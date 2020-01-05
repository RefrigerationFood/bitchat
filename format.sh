#!/usr/bin/env bash

#clang-format should be 6th or higher version
find . -name \*.hpp -o  -name \*.cpp | xargs clang-format -i