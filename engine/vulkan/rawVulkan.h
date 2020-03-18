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

/* Raw Rendering Engine - "engine/vulkan/rawVulkan.h"
 *
 * Vulkan runtime function loading
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 18/03/2020
 */

#ifndef RAW_VULKAN_H
#define RAW_VULKAN_H

#include <engine/platform/rawPlatform.h>

#include <vulkan/vulkan.h>

#include <stdbool.h>

/*
 * Vulkan loader function
 */
#define vkGetInstanceProcAddr \
	rawVkGetInstanceProcAddr
extern PFN_vkGetInstanceProcAddr
	vkGetInstanceProcAddr;

/*
 * Vulkan global level functions
 */
#define vkEnumerateInstanceExtensionProperties \
	rawVkEnumerateInstanceExtensionProperties
extern PFN_vkEnumerateInstanceExtensionProperties
	vkEnumerateInstanceExtensionProperties;

#define vkEnumerateInstanceLayerProperties \
	rawVkEnumerateInstanceLayerProperties
extern PFN_vkEnumerateInstanceLayerProperties
	vkEnumerateInstanceLayerProperties;

#define vkCreateInstance \
	rawVkCreateInstance
extern PFN_vkCreateInstance
	vkCreateInstance;

/*
 * Vulkan instance level functions
 */
#define vkEnumeratePhysicalDevices \
	rawVkEnumeratePhysicalDevices
extern PFN_vkEnumeratePhysicalDevices
	vkEnumeratePhysicalDevices;

#define vkEnumerateDeviceExtensionProperties \
	rawVkEnumerateDeviceExtensionProperties
extern PFN_vkEnumerateDeviceExtensionProperties
	vkEnumerateDeviceExtensionProperties;

#define vkEnumerateDeviceLayerProperties \
	rawVkEnumerateDeviceLayerProperties
extern PFN_vkEnumerateDeviceLayerProperties
	vkEnumerateDeviceLayerProperties;

#define vkGetPhysicalDeviceFeatures \
	rawVkGetPhysicalDeviceFeatures
extern PFN_vkGetPhysicalDeviceFeatures
	vkGetPhysicalDeviceFeatures;

#define vkGetPhysicalDeviceProperties \
	rawVkGetPhysicalDeviceProperties
extern PFN_vkGetPhysicalDeviceProperties
	vkGetPhysicalDeviceProperties;

#define vkGetPhysicalDeviceQueueFamilyProperties \
	rawVkGetPhysicalDeviceQueueFamilyProperties
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties
	vkGetPhysicalDeviceQueueFamilyProperties;

#define vkGetPhysicalDeviceMemoryProperties \
	rawVkGetPhysicalDeviceMemoryProperties
extern PFN_vkGetPhysicalDeviceMemoryProperties
	vkGetPhysicalDeviceMemoryProperties;

#define vkGetPhysicalDeviceFormatProperties \
	rawVkGetPhysicalDeviceFormatProperties
extern PFN_vkGetPhysicalDeviceFormatProperties
	vkGetPhysicalDeviceFormatProperties;

#define vkCreateDevice \
	rawVkCreateDevice
extern PFN_vkCreateDevice
	vkCreateDevice;

#define vkGetDeviceProcAddr \
	rawVkGetDeviceProcAddr
extern PFN_vkGetDeviceProcAddr
	vkGetDeviceProcAddr;

#define vkDestroyInstance \
	rawVkDestroyInstance
extern PFN_vkDestroyInstance
	vkDestroyInstance;

/*
 * Vulkan instance level extensions
 */
#define vkGetPhysicalDeviceSurfaceSupportKHR \
	rawVkGetPhysicalDeviceSurfaceSupportKHR
extern PFN_vkGetPhysicalDeviceSurfaceSupportKHR
	vkGetPhysicalDeviceSurfaceSupportKHR;

#define vkGetPhysicalDeviceSurfaceCapabilitiesKHR \
	rawVkGetPhysicalDeviceSurfaceCapabilitiesKHR
extern PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR;

#define vkGetPhysicalDeviceSurfaceFormatsKHR \
	rawVkGetPhysicalDeviceSurfaceFormatsKHR
extern PFN_vkGetPhysicalDeviceSurfaceFormatsKHR
	vkGetPhysicalDeviceSurfaceFormatsKHR;

#define vkGetPhysicalDeviceSurfacePresentModesKHR \
	rawVkGetPhysicalDeviceSurfacePresentModesKHR
extern PFN_vkGetPhysicalDeviceSurfacePresentModesKHR
	vkGetPhysicalDeviceSurfacePresentModesKHR;

#define vkDestroySurfaceKHR \
	rawVkDestroySurfaceKHR
extern PFN_vkDestroySurfaceKHR
	vkDestroySurfaceKHR;

#if defined (RAW_PLATFORM_LINUX)
#if defined (RAW_PLATFORM_XCB_WINDOW_SYSTEM)
#define vkCreateXcbSurfaceKHR \
	rawVkCreateXcbSurfaceKHR
extern PFN_vkCreateXcbSurfaceKHR
	vkCreateXcbSurfaceKHR;
#endif
#endif

/*
 * Loads Vulkan runtime library, vkGetInstanceProcAddr
 * and Vulkan global level functions.
 */
bool rawLoadVulkan(RAW_VULKAN_LIBRARY vulkan);

/*
 * Loads Vulkan intance level functions and extensions.
 * All extensions required by the engine must be present on the hardware.
 */
bool rawLoadVulkanInstanceLevelFunctions(
	VkInstance instance,
	char const* const* enabled_extensions,
	uint32_t n_enabled_extensions);

#endif // RAW_VULKAN_H

