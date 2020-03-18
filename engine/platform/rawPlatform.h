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
 * Last modified: 18/03/2020
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
 ******** Terminal functionalities
 *********************************/
void rawPlatformSwitchTerminalColor(RawPlatformTerminalColor color);

/*********************************
 * Dynamic library functionalities
 *********************************/
#include <dlfcn.h>

#define RAW_LOAD_LIBRARY_FUNCTION(library, function) dlsym(library, function)

/********************************
 ************************* Vulkan
 ********************************/
#define RAW_VULKAN_LIBRARY void*

#define RAW_LOAD_VULKAN_LIBRARY(library) \
	library = dlopen("libvulkan.so.1", RTLD_NOW)

#if defined (RAW_PLATFORM_XCB_WINDOW_SYSTEM)
#define VK_USE_PLATFORM_XCB_KHR
#elif defined (RAW_PLATFORM_XLIB_WINDOW_SYSTEM)
#define VK_USE_PLATFORM_XLIB_KHR
#endif

///--------------------------------------------------------------------- WINDOWS
#elif defined (RAW_PLATFORM_WINDOWS)

#if !defined (WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

// TODO: RAW_LOAD_VULKAN_LIBRARY, RAW_LOAD_LIBRARY_FUNCTION

#define RAW_VULKAN_LIBRARY HMODULE
#define VK_USE_PLATFORM_WIN32_KHR

#endif // Operating system switch

#endif // RAW_PLATFORM_H

