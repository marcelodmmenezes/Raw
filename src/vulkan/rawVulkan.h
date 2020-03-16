/*
 * MIT License
 * 
 * Copyright (c) 2020 Marcelo de Matos Menezes
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef RAW_VULKAN_H
#define RAW_VULKAN_H

#if defined (RAW_PLATFORM_LINUX)
#	include <dlfcn.h>
#	define VULKAN_LIBRARY void*
#	if defined (RAW_PLATFORM_XCB_WINDOW_SYSTEM)
#		define VK_USE_PLATFORM_XCB_KHR
#	elif defined (RAW_PLATFORM_XLIB_WINDOW_SYSTEM)
#		define VK_USE_PLATFORM_XLIB_KHR
#	endif
#elif defined (RAW_PLATFORM_WINDOWS)
#	if !defined (WIN32_LEAN_AND_MEAN)
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <windows.h>
#	define VULKAN_LIBRARY HMODULE
#	define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.h>

#include <stdbool.h>

#define vkGetInstanceProcAddr rawVkGetInstanceProcAddr
extern PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;

bool loadVulkan(VULKAN_LIBRARY vulkan);

#endif // RAW_VULKAN_H

