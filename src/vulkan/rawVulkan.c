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

/* Raw Rendering Engine - "src/vulkan/rawVulkan.c"
 *
 * Vulkan runtime function loading
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 16/03/2020
 */

#include <src/vulkan/rawVulkan.h>

// TODO: Implement log library
#include <stdio.h>

PFN_vkGetInstanceProcAddr
	vkGetInstanceProcAddr;
PFN_vkEnumerateInstanceExtensionProperties
	vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties
	vkEnumerateInstanceLayerProperties;
PFN_vkCreateInstance
	vkCreateInstance;

bool rawLoadVulkan(RAW_VULKAN_LIBRARY vulkan) {
	RAW_LOAD_VULKAN_LIBRARY(vulkan);

	if (!vulkan) {
		puts("ERROR: Vulkan Runtime library connection failed!");
		return false;
	}

	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)
		RAW_LOAD_LIBRARY_FUNCTION(vulkan, "vkGetInstanceProcAddr");

	if (!vkGetInstanceProcAddr) {
		puts("ERROR: vkGetInstanceProcAddr could not be loaded!");
		return false;
	}

#define LOAD(func)                                                 \
	func = (PFN_##func)vkGetInstanceProcAddr(RAW_NULL_PTR, #func); \
	                                                               \
	if (!func) {                                                   \
		puts("ERROR: " #func " could not be loaded!");             \
		return false;                                              \
	}

	LOAD(vkEnumerateInstanceExtensionProperties);
	LOAD(vkEnumerateInstanceLayerProperties);
	LOAD(vkCreateInstance);
#undef LOAD

	return true;
}

