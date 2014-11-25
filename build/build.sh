#!/bin/bash
export LD_LIBRARY_PATH=./
export CPLUS_INCLUDE_PATH=../src
g++ ../src/device/framebuffer/graphics_device.cpp --share -fPIC -o libdevice-framebuffer.so
g++ ../test/unittest/device/framebuffer/test_framebuffer_device.cpp libdevice-framebuffer.so -o test_framebuffer_device.out
