#!/usr/bin/env bash

BUILD_DIR_NAME="CMakeOutput"
SCRIPT_PATH=$(pwd)

if [ ! -d "${BUILD_DIR_NAME}" ]; then
  # Control will enter here if ${BUILD_DIR_NAME} doesn't exist.
  mkdir ${BUILD_DIR_NAME}
fi
cd ${BUILD_DIR_NAME}
cmake ${SCRIPT_PATH}
make