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

#include <src/vulkan/rawVulkan.h>

// TODO: Implement log library
#include <stdio.h>

PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;

bool loadVulkan(VULKAN_LIBRARY vulkan) {
#if defined (RAW_PLATFORM_LINUX)
	vulkan = dlopen("libvulkan.so.1", RTLD_NOW);
#endif

	if (!vulkan) {
		puts("ERROR: Vulkan Runtime library connection failed!");
		return false;
	}

	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)
#if defined (RAW_PLATFORM_LINUX)
		dlsym(vulkan, "vkGetInstanceProcAddr");
#endif

	if (!vkGetInstanceProcAddr) {
		puts("ERROR: vkGetInstanceProcAddr could not be loaded!");
		return false;
	}

	return true;
}

