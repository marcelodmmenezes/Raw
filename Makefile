## MIT License
##
## Copyright (c) 2020 Marcelo de Matos Menezes
##
## Permission is hereby granted, free of charge, to any person obtaining a copy
## of this software and associated documentation files (the "Software"), to deal
## in the Software without restriction, including without limitation the rights
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
## copies of the Software, and to permit persons to whom the Software is
## furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included in
## all copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
## SOFTWARE.

## Raw Rendering Engine - "Makefile"
##
## Basic Makefile for testing
## TODO: Reduce compilation time
##
## Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
## Created: 16/03/2020
## Last modified: 16/03/2020

unitTestsXCB:
	gcc -std=c11                                            \
	src/unitTests/rawLinuxXCB.c                             \
	src/vulkan/rawVulkan.c                                  \
	src/vulkan/rawVulkanInstance.c                          \
	src/platform/linux/rawMemory.c                          \
	-o build/unitTests/unitTestsXCB.out                     \
	-I .                                                    \
	-D RAW_PLATFORM_LINUX -D RAW_PLATFORM_XCB_WINDOW_SYSTEM \
	-D RAW_NULL_PTR="(void*)0"                              \
	-D RAW_ENGINE_NAME="\"RAW Rendering Engine\""           \
	-D RAW_ENGINE_VERSION="VK_MAKE_VERSION(1, 0, 0)"        \
	-D RAW_VULKAN_VERSION="VK_MAKE_VERSION(1, 0, 0)"        \
	-ldl

