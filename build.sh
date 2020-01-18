#!/usr/bin/env bash

BUILD_DIR_NAME="CMakeOutput"
SCRIPT_PATH=$(pwd)
THREAD_COUNT=$(nproc --all)
FLAGS=""

if [[ $* == *--clean* ]]; then
  echo "*** CLEAN BUILD ***"
  rm -rf ${BUILD_DIR_NAME}/*
fi

if [[ $* == *--ccache* ]]; then
  FLAGS+="-DCMAKE_CXX_COMPILER_LAUNCHER=ccache "
fi

if [ ! -d "${BUILD_DIR_NAME}" ]; then
  # Control will enter here if ${BUILD_DIR_NAME} doesn't exist.
  echo "*** MAKE DIR ${BUILD_DIR_NAME} ***"
  mkdir ${BUILD_DIR_NAME}
fi

cd ${BUILD_DIR_NAME} || exit
cmake  "${FLAGS}" "${SCRIPT_PATH}"
make -j"${THREAD_COUNT}"