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

/* Raw Rendering Engine - "engine/platform/rawPlatform.h"
 *
 * Operating system abstraction API
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 08/04/2020
 */

#ifndef RAW_PLATFORM_H
#define RAW_PLATFORM_H

///-------------------------------------------------------------- CROSS PLATFORM
/*********************************
 ******** Terminal functionalities
 *********************************/
typedef enum {
	RAW_PLATFORM_TERMINAL_COLOR_RED,
	RAW_PLATFORM_TERMINAL_COLOR_BOLD_RED,
	RAW_PLATFORM_TERMINAL_COLOR_GREEN,
	RAW_PLATFORM_TERMINAL_COLOR_BOLD_GREEN,
	RAW_PLATFORM_TERMINAL_COLOR_YELLOW,
	RAW_PLATFORM_TERMINAL_COLOR_BOLD_YELLOW,
	RAW_PLATFORM_TERMINAL_COLOR_BLUE,
	RAW_PLATFORM_TERMINAL_COLOR_BOLD_BLUE,
	RAW_PLATFORM_TERMINAL_COLOR_MAGENTA,
	RAW_PLATFORM_TERMINAL_COLOR_BOLD_MAGENTA,
	RAW_PLATFORM_TERMINAL_COLOR_CYAN,
	RAW_PLATFORM_TERMINAL_COLOR_BOLD_CYAN,
	RAW_PLATFORM_TERMINAL_COLOR_DEFAULT
} RawPlatformTerminalColor;

///----------------------------------------------------------------------- LINUX
#if defined (RAW_PLATFORM_LINUX)

/*********************************
 * Dynamic library functionalities
 *********************************/
#include <dlfcn.h>

#define RAW_LOAD_LIBRARY_FUNCTION(library, function) \
	dlsym(library, function)

/*********************************
 ******** Terminal functionalities
 *********************************/
void rawPlatformSwitchTerminalColor(RawPlatformTerminalColor color);

/*********************************
 ************************** Vulkan
 *********************************/
#define RAW_VULKAN_LIBRARY \
 	void*

#define RAW_LOAD_VULKAN_LIBRARY(library)         \
	library = dlopen("libvulkan.so.1", RTLD_NOW)

#define RAW_RELEASE_VULKAN_LIBRARY(library) \
	dlclose(library);

#if defined (RAW_PLATFORM_XCB_WINDOW_SYSTEM)
#define VK_USE_PLATFORM_XCB_KHR
#define RAW_VULKAN_SURFACE_CREATE_INFO \
	VkXcbSurfaceCreateInfoKHR
#define RAW_VULKAN_SURFACE_CREATE_INFO_TYPE \
	VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR
#define RAW_VULKAN_SURFACE_DISPLAY xcb_connection_t*
#define RAW_VULKAN_SURFACE_CREATION_PLATFORM_PARAMETER_1 connection
#define RAW_VULKAN_SURFACE_WINDOW xcb_window_t
#define RAW_VULKAN_SURFACE_CREATION_PLATFORM_PARAMETER_2 window
#define RAW_VULKAN_CREATE_SURFACE(...) \
	vkCreateXcbSurfaceKHR(__VA_ARGS__)
#elif defined (RAW_PLATFORM_XLIB_WINDOW_SYSTEM)
#define VK_USE_PLATFORM_XLIB_KHR
// TODO: xlib surface creation type
#endif

///--------------------------------------------------------------------- WINDOWS
#elif defined (RAW_PLATFORM_WINDOWS)

#if !defined (WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

/*********************************
 * Dynamic library functionalities
 *********************************/
#define RAW_LOAD_LIBRARY_FUNCTION(library, function) \
	GetProcAddress(library, function)

/*********************************
 ******** Terminal functionalities
 *********************************/
void rawPlatformSwitchTerminalColor(RawPlatformTerminalColor color);

/*********************************
 ************************** Vulkan
 *********************************/
#define RAW_VULKAN_LIBRARY \
 	HMODULE

#define RAW_LOAD_VULKAN_LIBRARY(library) \
	library = LoadLibrary("vulkan-1.dll")

#define RAW_RELEASE_VULKAN_LIBRARY(library) \
	FreeLibrary(library)

#define VK_USE_PLATFORM_WIN32_KHR
// TODO: win32 surface creation type

#endif // Operating system switch

#endif // RAW_PLATFORM_H

