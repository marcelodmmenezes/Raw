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

/* Raw Rendering Engine - "engine/unitTests/rawLinuxXCB.c"
 *
 * Unit testing procedures
 * Linux, XCB
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 18/03/2020
 */

#include <engine/platform/rawMemory.h>
#include <engine/vulkan/rawVulkan.h>
#include <engine/vulkan/rawVulkanInstance.h>
#include <engine/vulkan/rawVulkanPhysicalDevice.h>

#include <assert.h>
#include <stdio.h>

void testMemoryAllocation() {
	puts("\033[0;34mRunning memory allocation test...\033[0m");
	fflush(stdout);

	void* ptr;
	RAW_MEM_ALLOC(ptr, 4294967296, __FILE__, __LINE__);
	assert(ptr && "RAW_MEM_ALLOC failed!");

	RAW_MEM_FREE(ptr, __FILE__, __LINE__);
	ptr = RAW_NULL_PTR;

	puts("\033[0;32mTest succeeded\n\033[0m");
	fflush(stdout);
}

void testVulkanLibraryLoading() {
	puts("\033[0;34mRunning Vulkan library loading test...\033[0m");
	fflush(stdout);

	RAW_VULKAN_LIBRARY vulkan;
	assert(rawLoadVulkan(vulkan) && "loadVulkan failed!");

	puts("\033[0;32mTest succeeded\n\033[0m");
	fflush(stdout);
}

void testVulkanInstanceCreationAndDestruction() {
	puts("\033[0;34mRunning Vulkan instance creation test...\033[0m");
	fflush(stdout);

	VkExtensionProperties* available_extensions = RAW_NULL_PTR;
	uint32_t n_available_extensions;

	assert(rawGetAvailableVulkanExtensions(
		&available_extensions, &n_available_extensions) &&
		"Vulkan extension enumeration failed!");

	VkInstance instance = VK_NULL_HANDLE;

	char const** desired_extensions = RAW_NULL_PTR;
	uint32_t n_desired_extensions = 0;

	assert(rawCreateVulkanInstance(&instance, available_extensions,
		n_available_extensions, desired_extensions, n_desired_extensions,
		"rawLinuxXCB", VK_MAKE_VERSION(1, 0, 0)) &&
		"Vulkan instance creation failed!");

	assert(rawLoadVulkanInstanceLevelFunctions(
		instance, desired_extensions, n_desired_extensions) &&
		"rawLoadVulkanInstanceLevelFunctions failed!");

	rawDestroyVulkanInstance(&instance);

	assert(instance == VK_NULL_HANDLE &&
		"Vulkan instance destruction failed!");

	RAW_MEM_FREE(available_extensions, __FILE__, __LINE__);
	available_extensions = RAW_NULL_PTR;

	puts("\033[0;32mTest succeeded\n\033[0m");
	fflush(stdout);
}

void testVulkanPhysicalDeviceCreationAndDestruction() {
	puts("\033[0;34mRunning Vulkan physical device creation test...\033[0m");
	fflush(stdout);

	// Instance creation
	VkExtensionProperties* available_extensions = RAW_NULL_PTR;
	uint32_t n_available_extensions;

	rawGetAvailableVulkanExtensions(
		&available_extensions, &n_available_extensions);

	VkInstance instance = VK_NULL_HANDLE;

	char const** desired_extensions = RAW_NULL_PTR;
	uint32_t n_desired_extensions = 0;

	rawCreateVulkanInstance(&instance, available_extensions,
		n_available_extensions, desired_extensions, n_desired_extensions,
		"rawLinuxXCB", VK_MAKE_VERSION(1, 0, 0));

	rawLoadVulkanInstanceLevelFunctions(
		instance, desired_extensions, n_desired_extensions);
	
	// Physical device creation
	VkPhysicalDevice* physical_devices = RAW_NULL_PTR;
	uint32_t n_physical_devices;

	assert(rawGetPhysicalDevices(instance,
		&physical_devices, &n_physical_devices) &&
		"rawGetPhysicalDevices failed!");

	for (uint32_t i = 0; i < n_physical_devices; ++i) {
		VkExtensionProperties* device_extensions = RAW_NULL_PTR;
		uint32_t n_device_extensions;

		VkQueueFamilyProperties* queue_families = RAW_NULL_PTR;
		uint32_t n_queue_families;

		VkPhysicalDeviceFeatures features;
		VkPhysicalDeviceProperties properties;

		assert(rawGetPhysicalDeviceCharacteristics(
			physical_devices[i], &device_extensions,
			&n_device_extensions, &features, &properties,
			&queue_families, &n_queue_families) &&
			"rawGetPhysicalDeviceCharacteristics failed!");

		uint32_t queue_family_index;

		assert(rawGetPhysicalDeviceQueueFamily(
			physical_devices[i], queue_families,
			n_queue_families, 0, &queue_family_index) &&
			"rawGetPhysicalDeviceQueueFamily failed!");

		RAW_MEM_FREE(queue_families, __FILE__, __LINE__);
		queue_families = RAW_NULL_PTR;

		RAW_MEM_FREE(device_extensions, __FILE__, __LINE__);
		device_extensions = RAW_NULL_PTR;
	}

	RAW_MEM_FREE(physical_devices, __FILE__, __LINE__);
	physical_devices = RAW_NULL_PTR;
	
	// Instance destruction
	rawDestroyVulkanInstance(&instance);
	instance == VK_NULL_HANDLE;

	RAW_MEM_FREE(available_extensions, __FILE__, __LINE__);
	available_extensions = RAW_NULL_PTR;

	puts("\033[0;32mTest succeeded\n\033[0m");
	fflush(stdout);
}

int main() {
	testMemoryAllocation();
	testVulkanLibraryLoading();
	testVulkanInstanceCreationAndDestruction();
	testVulkanPhysicalDeviceCreationAndDestruction();

	puts("\033[0;32mAll tests succeeded!\n\033[0m");
}

