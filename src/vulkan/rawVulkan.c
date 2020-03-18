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
 * NOTE: The LOAD macro functions calls are passing another
 * macros as arguments. The argument macros are expanded only
 * inside the LOAD macro function definition, not on the call.
 * When used with operators # and ## inside the definition,
 * the parameter is also not expanded, giving the LOAD macro functions
 * the expected result.
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 18/03/2020
 */

#include <src/vulkan/rawVulkan.h>

// TODO: Implement log library
#include <stdio.h>
#include <string.h>

/*
 * Vulkan loader function
 */
PFN_vkGetInstanceProcAddr
	vkGetInstanceProcAddr;

/*
 * Vulkan global level functions
 */
PFN_vkEnumerateInstanceExtensionProperties
	vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties
	vkEnumerateInstanceLayerProperties;
PFN_vkCreateInstance
	vkCreateInstance;

/*
 * Vulkan instance level functions
 */
PFN_vkEnumeratePhysicalDevices
	vkEnumeratePhysicalDevices;
PFN_vkEnumerateDeviceExtensionProperties
	vkEnumerateDeviceExtensionProperties;
PFN_vkEnumerateDeviceLayerProperties
	vkEnumerateDeviceLayerProperties;
PFN_vkGetPhysicalDeviceFeatures
	vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceProperties
	vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties
	vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceMemoryProperties
	vkGetPhysicalDeviceMemoryProperties;
PFN_vkGetPhysicalDeviceFormatProperties
	vkGetPhysicalDeviceFormatProperties;
PFN_vkCreateDevice
	vkCreateDevice;
PFN_vkGetDeviceProcAddr
	vkGetDeviceProcAddr;
PFN_vkDestroyInstance
	vkDestroyInstance;

/*
 * Vulkan instance level extensions
 */
PFN_vkGetPhysicalDeviceSurfaceSupportKHR
	vkGetPhysicalDeviceSurfaceSupportKHR;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR
	vkGetPhysicalDeviceSurfaceFormatsKHR;
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR
	vkGetPhysicalDeviceSurfacePresentModesKHR;
PFN_vkDestroySurfaceKHR
	vkDestroySurfaceKHR;
PFN_vkCreateXcbSurfaceKHR
	vkCreateXcbSurfaceKHR;

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

bool rawLoadVulkanInstanceLevelFunctions(
	VkInstance instance,
	char const* const* enabled_extensions,
	uint32_t n_enabled_extensions) {

#define LOAD(func)                                             \
	func = (PFN_##func)vkGetInstanceProcAddr(instance, #func); \
                                                               \
	if (!func) {                                               \
		puts("ERROR: " #func " could not be loaded!");         \
		return false;                                          \
	}

	LOAD(vkEnumeratePhysicalDevices);
	LOAD(vkEnumerateDeviceExtensionProperties);
	LOAD(vkGetPhysicalDeviceFeatures);
	LOAD(vkGetPhysicalDeviceProperties);
	LOAD(vkGetPhysicalDeviceQueueFamilyProperties);
	LOAD(vkGetPhysicalDeviceMemoryProperties);
	LOAD(vkGetPhysicalDeviceFormatProperties);
	LOAD(vkCreateDevice);
	LOAD(vkGetDeviceProcAddr);
	LOAD(vkDestroyInstance);
#undef LOAD

#define LOAD(func, extension)                                          \
	for (uint32_t i = 0; i < n_enabled_extensions; ++i) {              \
		if (strcmp(enabled_extensions[i], extension) == 0) {           \
			func = (PFN_##func)vkGetInstanceProcAddr(instance, #func); \
                                                                       \
			if (!func) {                                               \
				puts("ERROR: " #func " could not be loaded!");         \
				return false;                                          \
			}                                                          \
		}                                                              \
	}

	LOAD(vkGetPhysicalDeviceSurfaceSupportKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);
	LOAD(vkGetPhysicalDeviceSurfaceCapabilitiesKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);
	LOAD(vkGetPhysicalDeviceSurfaceFormatsKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);
	LOAD(vkGetPhysicalDeviceSurfacePresentModesKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);
	LOAD(vkDestroySurfaceKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);

#if defined (RAW_PLATFORM_LINUX)
#if defined (RAW_PLATFORM_XCB_WINDOW_SYSTEM)
	LOAD(vkCreateXcbSurfaceKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);
#endif
#endif
#undef LOAD

	return true;
}

