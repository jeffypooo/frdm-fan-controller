#!/usr/bin/env bash

export GCC_ARM_TOOLCHAIN=/home/jeff/toolchains/gcc-arm-none-eabi-6-2017-q2-update
PRJ_DIR=`pwd`
TC_FILE=${PRJ_DIR}/cmake/gcc-arm.cmake
SPD_BUILD_DIR=${PRJ_DIR}/spdlog_build
TC_INST_DIR=${GCC_ARM_TOOLCHAIN}/arm-none-eabi/local

echo "Working directory: $PRJ_DIR"
echo "Toolchain file: $TC_FILE"
echo "Build directory: $SPD_BUILD_DIR"

if [ -d ${SPD_BUILD_DIR} ]; then
    echo "Cleaning..."
    sudo rm -rf ${SPD_BUILD_DIR}
fi

mkdir ${SPD_BUILD_DIR} && cd ${SPD_BUILD_DIR}
echo "Running CMake..."
CXX_FLAGS="-Og -fpermissive -fexceptions -Wfatal-errors"
cmake "../ext/spdlog/" "-DCMAKE_INSTALL_PREFIX=$TC_INST_DIR" "-DCMAKE_TOOLCHAIN_FILE=$TC_FILE" "-DSPDLOG_BUILD_EXAMPLES=OFF" "-DSPDLOG_BUILD_TESTING=OFF" "-DCMAKE_CXX_FLAGS=$CXX_FLAGS"
echo "Running make..."
make
echo "Installing..."
sudo make install