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

/* Raw Rendering Engine - "engine/vulkan/rawVulkanPhysicalDevice.c"
 *
 * Vulkan physical device related functions
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 18/03/2020
 * Last modified: 18/03/2020
 */

#include <engine/vulkan/rawVulkanPhysicalDevice.h>
#include <engine/platform/rawMemory.h>

#include <assert.h>

// TODO: Implement log library
#include <stdio.h>

bool rawGetPhysicalDevices(
	VkInstance instance,
	VkPhysicalDevice** available_devices,
	uint32_t* n_available_devices) {

	VkResult result = vkEnumeratePhysicalDevices(
		instance, n_available_devices, RAW_NULL_PTR);

	if (result != VK_SUCCESS) {
		puts("ERROR: vkEnumeratePhysicalDevices failed!");
		return false;
	}

	RAW_MEM_ALLOC(*available_devices,
		*n_available_devices * sizeof(VkPhysicalDevice),
		__FILE__, __LINE__);

	if (!*available_devices) {
		RAW_MEM_FREE(*available_devices, __FILE__, __LINE__);
		*available_devices = RAW_NULL_PTR;
		puts("ERROR: RAW_MEM_ALLOC failed on rawEnumeratePhysicalDevices!");
		return false;
	}

	result = vkEnumeratePhysicalDevices(
		instance, n_available_devices, *available_devices);

	if (result != VK_SUCCESS) {
		RAW_MEM_FREE(*available_devices, __FILE__, __LINE__);
		*available_devices = RAW_NULL_PTR;
		puts("ERROR: vkEnumeratePhysicalDevices failed!");
		return false;
	}

	return true;
}

bool rawGetPhysicalDeviceCharacteristics(
	VkPhysicalDevice physical_device,
	VkExtensionProperties** available_extensions,
	uint32_t* n_available_extensions,
	VkPhysicalDeviceFeatures* features,
	VkPhysicalDeviceProperties* properties,
	VkQueueFamilyProperties** queue_families,
	uint32_t* n_queue_families) {

	// Second parameter is the layer name
	VkResult result = vkEnumerateDeviceExtensionProperties(
		physical_device, RAW_NULL_PTR,
		n_available_extensions, RAW_NULL_PTR);

	if (result != VK_SUCCESS) {
		puts("ERROR: vkEnumerateDeviceExtensionProperties failed!");
		return false;
	}

	RAW_MEM_ALLOC(*available_extensions,
		*n_available_extensions * sizeof(VkExtensionProperties),
		__FILE__, __LINE__);

	if (!*available_extensions) {
		RAW_MEM_FREE(*available_extensions, __FILE__, __LINE__);
		*available_extensions = RAW_NULL_PTR;
		puts("ERROR: RAW_MEM_ALLOC failed on rawGetPhysicalDeviceExtensions!");
		return false;
	}

	result = vkEnumerateDeviceExtensionProperties(
		physical_device, RAW_NULL_PTR,
		n_available_extensions, *available_extensions);

	if (result != VK_SUCCESS) {
		RAW_MEM_FREE(*available_extensions, __FILE__, __LINE__);
		*available_extensions = RAW_NULL_PTR;
		puts("ERROR: vkEnumerateDeviceExtensionProperties failed!");
		return false;
	}

	vkGetPhysicalDeviceFeatures(physical_device, features);
	vkGetPhysicalDeviceProperties(physical_device, properties);

	vkGetPhysicalDeviceQueueFamilyProperties(
		physical_device, n_queue_families, RAW_NULL_PTR);

	if (*n_queue_families == 0) {
		RAW_MEM_FREE(available_extensions, __FILE__, __LINE__);
		available_extensions = RAW_NULL_PTR;
		puts("ERROR: physical device doesn't have "
			"any queue families available!");
		return false;
	}

	RAW_MEM_ALLOC(*queue_families,
		*n_queue_families * sizeof(VkQueueFamilyProperties),
		__FILE__, __LINE__);

	vkGetPhysicalDeviceQueueFamilyProperties(
		physical_device, n_queue_families, *queue_families);

	if (*n_queue_families == 0) {
		RAW_MEM_FREE(available_extensions, __FILE__, __LINE__);
		available_extensions = RAW_NULL_PTR;
		RAW_MEM_FREE(*queue_families, __FILE__, __LINE__);
		*queue_families = RAW_NULL_PTR;
		puts("ERROR: physical device doesn't have "
			"any queue families available!");

		return false;
	}

	return true;
}

bool rawGetPhysicalDeviceQueueFamily(
	VkPhysicalDevice physical_device,
	VkQueueFamilyProperties* const queue_families,
	uint32_t n_queue_families,
	VkQueueFlags desired_capabilities,
	uint32_t* queue_family_index) {

	for (uint32_t i = 0; i < n_queue_families; ++i) {
		if ((queue_families[i].queueCount > 0u) &&
			(queue_families[i].queueFlags &
			desired_capabilities) == desired_capabilities) {
			*queue_family_index = i;
			return true;
		}
	}

	return false;
}

