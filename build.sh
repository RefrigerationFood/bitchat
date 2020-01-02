#!/usr/bin/env bash

BUILD_DIR_NAME="CMakeOutput"
SCRIPT_PATH=$(pwd)

mkdir ${BUILD_DIR_NAME}
cd ${BUILD_DIR_NAME}
cmake ${SCRIPT_PATH}
make