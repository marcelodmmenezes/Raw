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
 * Last modified: 19/03/2020
 */

#include <engine/platform/rawMemory.h>
#include <engine/vulkan/rawVulkan.h>
#include <engine/vulkan/rawVulkanInstance.h>
#include <engine/vulkan/rawVulkanPhysicalDevice.h>
#include <engine/vulkan/rawVulkanLogicalDevice.h>
#include <engine/utils/rawLogger.h>
#include <engine/utils/rawAssert.h>

// Not exactly a unit test but useful anyways
void testLoggingLibrary() {
	RAW_LOG_CMSG("Running logging test...\n", RAW_LOG_BLUE);

	RAW_LOG_MSG("RAW_LOG_MSG\n");
	RAW_LOG_CMSG("RAW_LOG_CMSG\n", RAW_LOG_CYAN);
	RAW_LOG_TRACE("RAW_LOG_TRACE %d", 1);
	RAW_LOG_INFO("RAW_LOG_INFO %d", 2);
	RAW_LOG_WARNING("RAW_LOG_WARNING %d", 3);
	RAW_LOG_ERROR("RAW_LOG_ERROR %d", 4);

	RAW_LOG_CMSG("Test succeeded!\n\n", RAW_LOG_GREEN);
}

void testMemoryAllocation() {
	RAW_LOG_CMSG("Running memory allocation test...\n", RAW_LOG_BLUE);

	void* ptr;
	RAW_MEM_ALLOC(ptr, 4294967296, 1);
	RAW_ASSERT(ptr, "RAW_MEM_ALLOC failed!");

	RAW_MEM_FREE(ptr);

	RAW_LOG_CMSG("Test succeeded!\n\n", RAW_LOG_GREEN);
}

void testVulkanLibraryLoading() {
	RAW_LOG_CMSG("Running Vulkan library loading test...\n", RAW_LOG_BLUE);

	RAW_VULKAN_LIBRARY vulkan = RAW_NULL_PTR;

	bool result = rawLoadVulkan(&vulkan);

	RAW_ASSERT(result, "loadVulkan failed!");

	rawReleaseVulkan(&vulkan);

	RAW_LOG_CMSG("Test succeeded!\n\n", RAW_LOG_GREEN);
}

void testVulkanInstanceCreationAndDestruction() {
	RAW_LOG_CMSG("Running Vulkan instance creation test...\n", RAW_LOG_BLUE);

	RAW_VULKAN_LIBRARY vulkan = RAW_NULL_PTR;
	rawLoadVulkan(&vulkan);

	VkExtensionProperties* available_extensions = RAW_NULL_PTR;
	uint32_t n_available_extensions;

	bool result = rawGetAvailableVulkanInstanceExtensions(
		&available_extensions, &n_available_extensions);

	RAW_ASSERT(result, "Vulkan extension enumeration failed!");

	VkInstance instance = VK_NULL_HANDLE;

	char const** desired_extensions = RAW_NULL_PTR;
	uint32_t n_desired_extensions = 0;

	result = rawCreateVulkanInstance(&instance, available_extensions,
		n_available_extensions, desired_extensions, n_desired_extensions,
		"rawLinuxXCB", VK_MAKE_VERSION(1, 0, 0));

	RAW_ASSERT(result, "Vulkan instance creation failed!");

	result = rawLoadVulkanInstanceLevelFunctions(
		instance, desired_extensions, n_desired_extensions);

	RAW_ASSERT(result, "rawLoadVulkanInstanceLevelFunctions failed!");

	// Instance destruction
	rawDestroyVulkanInstance(&instance);

	RAW_ASSERT(instance == VK_NULL_HANDLE,
		"Vulkan instance destruction failed!");

	RAW_MEM_FREE(available_extensions);

	rawReleaseVulkan(&vulkan);

	RAW_LOG_CMSG("Test succeeded!\n\n", RAW_LOG_GREEN);
}

void testVulkanPhysicalDeviceCreationAndDestruction() {
	RAW_LOG_CMSG("Running Vulkan physical device "
		"creation test...\n", RAW_LOG_BLUE);

	RAW_VULKAN_LIBRARY vulkan = RAW_NULL_PTR;
	rawLoadVulkan(&vulkan);

	// Instance creation
	VkExtensionProperties* available_extensions = RAW_NULL_PTR;
	uint32_t n_available_extensions;

	rawGetAvailableVulkanInstanceExtensions(
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

	bool result = rawGetVulkanPhysicalDevices(
		instance, &physical_devices, &n_physical_devices);

	RAW_ASSERT(result, "rawGetPhysicalDevices failed!");

	for (uint32_t i = 0; i < n_physical_devices; ++i) {
		VkExtensionProperties* device_extensions = RAW_NULL_PTR;
		uint32_t n_device_extensions;

		VkQueueFamilyProperties* queue_families = RAW_NULL_PTR;
		uint32_t n_queue_families;

		VkPhysicalDeviceFeatures features;
		VkPhysicalDeviceProperties properties;

		result = rawGetVulkanPhysicalDeviceCharacteristics(
			physical_devices[i], &device_extensions,
			&n_device_extensions, &features, &properties,
			&queue_families, &n_queue_families);

		RAW_ASSERT(result, "rawGetPhysicalDeviceCharacteristics failed!");

		uint32_t queue_family_index;

		result = rawGetVulkanPhysicalDeviceQueueFamilyIndex(
			physical_devices[i], queue_families,
			n_queue_families, 0, &queue_family_index);

		RAW_ASSERT(result, "rawGetPhysicalDeviceQueueFamily failed!");

		RAW_MEM_FREE(queue_families);
		RAW_MEM_FREE(device_extensions);
	}

	RAW_MEM_FREE(physical_devices);
	
	// Instance destruction
	rawDestroyVulkanInstance(&instance);

	RAW_MEM_FREE(available_extensions);

	rawReleaseVulkan(&vulkan);

	RAW_LOG_CMSG("Test succeeded!\n\n", RAW_LOG_GREEN);
}

void testRawSelectPhysicalDeviceWithDesiredCharacteristics() {
	RAW_LOG_CMSG("Running RAW Vulkan physical device "
		"selection test...\n", RAW_LOG_BLUE);

	RAW_VULKAN_LIBRARY vulkan = RAW_NULL_PTR;
	rawLoadVulkan(&vulkan);

	// Instance creation
	VkExtensionProperties* available_extensions = RAW_NULL_PTR;
	uint32_t n_available_extensions;

	rawGetAvailableVulkanInstanceExtensions(
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

	rawGetVulkanPhysicalDevices(
		instance, &physical_devices, &n_physical_devices);

	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceProperties properties;

	// rawSelectPhysicalDeviceWithDesiredCharacteristics test
	VkQueueFlags* desired_queue_capabilities = RAW_NULL_PTR;
	uint32_t n_desired_queue_capabilities = 0;

	float* queue_priorities = RAW_NULL_PTR;
	uint32_t n_queue_priorities;

	VkDeviceQueueCreateInfo* queue_create_infos = RAW_NULL_PTR;
	uint32_t n_queue_create_infos;

	uint32_t physical_device_index;

	bool result = rawSelectPhysicalDeviceWithDesiredCharacteristics(
		physical_devices, n_physical_devices,
		desired_extensions, n_desired_extensions,
		&features, &properties,
		desired_queue_capabilities, n_desired_queue_capabilities,
		&queue_priorities, &n_queue_priorities,
		&queue_create_infos, &n_queue_create_infos,
		&physical_device_index);

	RAW_ASSERT(result,
		"rawSelectPhysicalDeviceWithDesiredCharacteristics failed!");

	RAW_LOG_INFO("Selecting physical device %d", physical_device_index);

	RAW_MEM_FREE(queue_create_infos);
	RAW_MEM_FREE(queue_priorities);
	RAW_MEM_FREE(physical_devices);
	
	// Instance destruction
	rawDestroyVulkanInstance(&instance);

	RAW_MEM_FREE(available_extensions);

	rawReleaseVulkan(&vulkan);

	RAW_LOG_CMSG("Test succeeded!\n\n", RAW_LOG_GREEN);
}

void testVulkanLogicalDeviceCreationAndDestruction() {
	RAW_LOG_CMSG("Running RAW Vulkan logical device "
		"creation test...\n", RAW_LOG_BLUE);

	RAW_VULKAN_LIBRARY vulkan = RAW_NULL_PTR;
	rawLoadVulkan(&vulkan);

	// Instance creation
	VkExtensionProperties* available_extensions = RAW_NULL_PTR;
	uint32_t n_available_extensions;

	rawGetAvailableVulkanInstanceExtensions(
		&available_extensions, &n_available_extensions);

	VkInstance instance = VK_NULL_HANDLE;

	char const** instance_extensions = RAW_NULL_PTR;
	uint32_t n_desired_extensions = 0;

	rawCreateVulkanInstance(&instance, available_extensions,
		n_available_extensions, instance_extensions, n_desired_extensions,
		"rawLinuxXCB", VK_MAKE_VERSION(1, 0, 0));

	rawLoadVulkanInstanceLevelFunctions(
		instance, instance_extensions, n_desired_extensions);
	
	// Physical device creation and selection
	VkPhysicalDevice* physical_devices = RAW_NULL_PTR;
	uint32_t n_physical_devices;

	rawGetVulkanPhysicalDevices(
		instance, &physical_devices, &n_physical_devices);

	char const** device_extensions = RAW_NULL_PTR;
	n_desired_extensions = 0;

	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceProperties properties;

	VkQueueFlags desired_queue_capabilities[] = {
		VK_QUEUE_GRAPHICS_BIT,
		VK_QUEUE_COMPUTE_BIT
	};

	uint32_t n_desired_queue_capabilities = 2;

	float* queue_priorities = RAW_NULL_PTR;
	uint32_t n_queue_priorities;

	VkDeviceQueueCreateInfo* queue_create_infos = RAW_NULL_PTR;
	uint32_t n_queue_create_infos;

	uint32_t physical_device_index;

	rawSelectPhysicalDeviceWithDesiredCharacteristics(
		physical_devices, n_physical_devices,
		device_extensions, n_desired_extensions,
		&features, &properties,
		desired_queue_capabilities, n_desired_queue_capabilities,
		&queue_priorities, &n_queue_priorities,
		&queue_create_infos, &n_queue_create_infos,
		&physical_device_index);

	RAW_LOG_INFO("Selecting physical device %d", physical_device_index);

	// Logical device creation
	VkDevice logical_device;

	bool result = rawCreateVulkanLogicalDevice(
		physical_devices[physical_device_index],
		queue_create_infos, n_queue_create_infos,
		device_extensions, n_desired_extensions,
		&features, &logical_device);

	RAW_ASSERT(result, "rawCreateVulkanLogicalDevice failed!");

	rawLoadVulkanDeviceLevelFunctions(logical_device,
		device_extensions, n_desired_extensions);

	rawDestroyVulkanLogicalDevice(&logical_device);

	RAW_MEM_FREE(queue_create_infos);
	RAW_MEM_FREE(queue_priorities);
	RAW_MEM_FREE(physical_devices);
	
	// Instance destruction
	rawDestroyVulkanInstance(&instance);

	RAW_MEM_FREE(available_extensions);

	rawReleaseVulkan(&vulkan);

	RAW_LOG_CMSG("Test succeeded!\n\n", RAW_LOG_GREEN);
}

int main() {
	testLoggingLibrary();
	testMemoryAllocation();
	testVulkanLibraryLoading();
	testVulkanInstanceCreationAndDestruction();
	testVulkanPhysicalDeviceCreationAndDestruction();
	testRawSelectPhysicalDeviceWithDesiredCharacteristics();
	testVulkanLogicalDeviceCreationAndDestruction();

	RAW_LOG_CMSG("All tests succeeded!\n", RAW_LOG_GREEN);
}

