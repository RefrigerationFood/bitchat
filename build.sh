#!/usr/bin/env bash

BUILD_DIR_NAME="CMakeOutput"
SCRIPT_PATH=$(pwd)

if [[ $* == *--clean* ]]; then
  echo "*** CLEAN BUILD ***"
  rm -rf ${BUILD_DIR_NAME}*
fi

if [ ! -d "${BUILD_DIR_NAME}" ]; then
  # Control will enter here if ${BUILD_DIR_NAME} doesn't exist.
  echo "*** MAKE DIR ${BUILD_DIR_NAME} ***"
  mkdir ${BUILD_DIR_NAME}
fi
cd ${BUILD_DIR_NAME} || exit
cmake "${SCRIPT_PATH}"
make