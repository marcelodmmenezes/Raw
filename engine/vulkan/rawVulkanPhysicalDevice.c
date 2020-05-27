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
 * Last modified: 24/05/2020
 */

#include <engine/vulkan/rawVulkanPhysicalDevice.h>
#include <engine/platform/rawMemory.h>
#include <engine/utils/rawLogger.h>

#include <string.h>

bool rawGetVulkanPhysicalDevices(
	VkInstance instance,
	VkPhysicalDevice** available_devices,
	uint32_t* n_available_devices) {

	VkResult result = vkEnumeratePhysicalDevices(
		instance, n_available_devices, RAW_NULL_PTR);

	if (result != VK_SUCCESS) {
		RAW_LOG_ERROR("vkEnumeratePhysicalDevices failed!");

		return false;
	}

	RAW_MEM_ALLOC(*available_devices, (uint64_t)*n_available_devices,
		sizeof(VkPhysicalDevice));

	if (!*available_devices) {
		RAW_LOG_ERROR("RAW_MEM_ALLOC failed on rawEnumeratePhysicalDevices!");

		RAW_MEM_FREE(*available_devices);

		return false;
	}

	result = vkEnumeratePhysicalDevices(
		instance, n_available_devices, *available_devices);

	if (result != VK_SUCCESS) {
		RAW_LOG_ERROR("vkEnumeratePhysicalDevices failed!");

		RAW_MEM_FREE(*available_devices);

		return false;
	}

	return true;
}

bool rawGetVulkanPhysicalDeviceCharacteristics(
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
		RAW_LOG_ERROR("vkEnumerateDeviceExtensionProperties failed!");

		return false;
	}

	RAW_MEM_ALLOC(*available_extensions, (uint64_t)*n_available_extensions,
		sizeof(VkExtensionProperties));

	if (!*available_extensions) {
		RAW_LOG_ERROR("RAW_MEM_ALLOC failed on "
			"rawGetPhysicalDeviceExtensions!");

		return false;
	}

	result = vkEnumerateDeviceExtensionProperties(
		physical_device, RAW_NULL_PTR,
		n_available_extensions, *available_extensions);

	if (result != VK_SUCCESS) {
		RAW_LOG_ERROR("vkEnumerateDeviceExtensionProperties failed!");

		RAW_MEM_FREE(*available_extensions);

		return false;
	}

	vkGetPhysicalDeviceFeatures(physical_device, features);
	vkGetPhysicalDeviceProperties(physical_device, properties);

	vkGetPhysicalDeviceQueueFamilyProperties(
		physical_device, n_queue_families, RAW_NULL_PTR);

	if (*n_queue_families == 0) {
		RAW_LOG_ERROR("physical device doesn't have "
			"any queue families available!");

		RAW_MEM_FREE(*available_extensions);

		return false;
	}

	RAW_MEM_ALLOC(*queue_families, (uint64_t)*n_queue_families,
		sizeof(VkQueueFamilyProperties));

	if (!*queue_families) {
		RAW_LOG_ERROR("RAW_MEM_ALLOC failed on "
			"rawGetPhysicalDeviceExtensions!");

		RAW_MEM_FREE(*available_extensions);

		return false;
	}

	vkGetPhysicalDeviceQueueFamilyProperties(
		physical_device, n_queue_families, *queue_families);

	if (*n_queue_families == 0) {
		RAW_LOG_ERROR("physical device doesn't have "
			"any queue families available!");

		RAW_MEM_FREE(*available_extensions);
		RAW_MEM_FREE(*queue_families);

		return false;
	}

	return true;
}

bool rawGetVulkanPhysicalDeviceQueueFamilyIndex(
	VkQueueFamilyProperties const* const queue_families,
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

// TODO: Improve queue selection
// (check when its better to have one or multiple queues)
bool rawSelectVulkanPhysicalDeviceWithDesiredCharacteristics(
	VkPhysicalDevice const* const physical_devices,
	uint32_t n_physical_devices,
	char const* const* const desired_extensions,
	uint32_t n_desired_extensions,
	VkPhysicalDeviceFeatures* features,
	VkPhysicalDeviceProperties* properties,
	VkQueueFlags* const desired_queue_capabilities,
	uint32_t n_desired_queue_capabilities,
	float** queue_priorities,
	uint32_t* n_queue_priorities,
	VkDeviceQueueCreateInfo** queue_create_infos,
	uint32_t* n_queue_create_infos,
	VkSurfaceKHR presentation_surface,
	uint32_t* presentation_queue_family_index,
	uint32_t* physical_device_index) {

	for (uint32_t i = 0; i < n_physical_devices; ++i) {
		VkExtensionProperties* device_extensions = RAW_NULL_PTR;
		uint32_t n_device_extensions;

		VkQueueFamilyProperties* queue_families = RAW_NULL_PTR;
		uint32_t n_queue_families;

		if (!rawGetVulkanPhysicalDeviceCharacteristics(
			physical_devices[i], &device_extensions, &n_device_extensions,
			features, properties, &queue_families, &n_queue_families)) {
			RAW_LOG_WARNING("rawGetVulkanPhysicalDeviceCharacteristics "
				"failed for physical device %d!", i);

			if (i < n_physical_devices - 1)
				continue;
			else {
				RAW_LOG_ERROR(
					"rawSelectPhysicalDeviceWithDesiredCharacteristics "
					"failed on rawGetVulkanPhysicalDeviceCharacteristics");

				return false;
			}
		}

		RAW_LOG_INFO("Checking physical device %d\n\t\t "
			"API version: %d\n\t\t Driver version: %d\n\t\t "
			"Vendor ID: %d\n\t\t Device ID: %d\n\t\t "
			"Device type: %d\n\t\t Device name: %s\n\t\t "
			"Number of queue families: %d\n", i,
			properties->apiVersion, properties->driverVersion,
			properties->vendorID, properties->deviceID,
			properties->deviceType, properties->deviceName,
			n_queue_families);

		// Checking extensions
		for (uint32_t i = 0; i < n_desired_extensions; ++i) {
			bool available = false;

			for (uint32_t j = 0; j < n_device_extensions; ++j) {
				if (strcmp(desired_extensions[i],
						device_extensions[j].extensionName) == 0) {
					available = true;

					break;
				}
			}

			if (!available) {
				RAW_LOG_INFO("Physical device %d does not support "
					"extension %s!\n", i, desired_extensions[i]);

				RAW_MEM_FREE(queue_families);
				RAW_MEM_FREE(device_extensions);
			
				if (i < n_physical_devices - 1)
					continue;
				else {
					RAW_LOG_ERROR("There is no physical device with "
						"the required extensions!");

					return false;
				}
			}
		}

		// Checking if the device supports the
		// presentation surface in case it's requested
		if (presentation_surface != VK_NULL_HANDLE) {
			VkBool32 presentation_supported = VK_FALSE;

			for (uint32_t j = 0; j < n_queue_families; ++j) {
				VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(
					physical_devices[i], j, presentation_surface,
					&presentation_supported);

				if (result != VK_SUCCESS)
					RAW_LOG_WARNING("vkGetPhysicalDeviceSurfaceSupportKHR "
						"failed for physical device %d, queue family %d!",
						i, j);

				if (presentation_supported == VK_TRUE) {
					RAW_LOG_INFO("Physical device %d supports presentation "
						"surface on queue family %d", i, j);

					*presentation_queue_family_index = j;

					break;
				}
			}

			if (presentation_supported == VK_FALSE) {
				RAW_LOG_INFO("Physical device %d doesn't support "
					"presentation surface!", i);

				RAW_MEM_FREE(queue_families);
				RAW_MEM_FREE(device_extensions);
			
				if (i < n_physical_devices - 1)
					continue;
				else {
					RAW_LOG_ERROR("There's no physical device "
						"with presentation surface support!");

					return false;
				}
			}
		}

		// Selecting queues with desired capabilities
		uint32_t* n_queues_per_queue_family = RAW_NULL_PTR;

		RAW_MEM_ALLOC(n_queues_per_queue_family,
			(uint64_t)n_queue_families, sizeof(uint32_t));

		if (!n_queues_per_queue_family) {
			RAW_LOG_ERROR("rawSelectPhysicalDeviceWithDesiredCharacteristics "
				"failed on allocation for n_queues_per_queue_family!");

			RAW_MEM_FREE(queue_families);
			RAW_MEM_FREE(device_extensions);
			
			return false;
		}

		bool physical_device_support_desired_queues = true;

		for (uint32_t j = 0; j < n_queue_families; ++j)
			n_queues_per_queue_family[j] = 0;

		for (uint32_t j = 0; j < n_desired_queue_capabilities; ++j) {
			uint32_t queue_family_index; 

			if (rawGetVulkanPhysicalDeviceQueueFamilyIndex(
				queue_families, n_queue_families,
				desired_queue_capabilities[j], &queue_family_index))
				++n_queues_per_queue_family[queue_family_index];
			else {
				physical_device_support_desired_queues = false;

				RAW_LOG_INFO(
					"rawGetVulkanPhysicalDeviceQueueFamilyIndex failed "
					"for physical device %d and desired queue capability "
					"%d!", i, j);

				break;
			}
		}

		if (physical_device_support_desired_queues) {
			*n_queue_create_infos = 0;
			*n_queue_priorities = 0;

			RAW_LOG_INFO("Querying physical device %d\n"
				"\t         Number of queue families: %d\n",
				i, n_queue_families);

			for (uint32_t j = 0; j < n_queue_families; ++j) {
				*n_queue_create_infos += (n_queues_per_queue_family[j] > 0);

				RAW_LOG_INFO("Chosen queues for queue family %d: %d",
					j, n_queues_per_queue_family[j]);

				if (n_queues_per_queue_family[j] > *n_queue_priorities)
					*n_queue_priorities = n_queues_per_queue_family[j];
			}

			RAW_MEM_ALLOC(*queue_priorities,
				(uint64_t)*n_queue_priorities, sizeof(float));

			RAW_MEM_ALLOC(*queue_create_infos,
				(uint64_t)*n_queue_create_infos,
				sizeof(VkDeviceQueueCreateInfo));

			if (!(*queue_priorities) || !(*queue_create_infos)) {
				RAW_LOG_ERROR(
					"rawSelectPhysicalDeviceWithDesiredCharacteristics "
					"failed on allocation for queue_priorities/"
					"queue_create_infos!");

				if (*queue_priorities) {
					RAW_MEM_FREE(*queue_priorities);
				}
				else if (*queue_create_infos) {
					RAW_MEM_FREE(*queue_create_infos);
				}

				RAW_MEM_FREE(n_queues_per_queue_family);
				RAW_MEM_FREE(queue_families);
				RAW_MEM_FREE(device_extensions);

				return false;
			}

			// TODO: Give different priorities for each queue
			for (uint32_t j = 0; j < *n_queue_priorities; ++j)
				(*queue_priorities)[j] = 0.9f;

			// Selecting necessary queues for logical device creation
			for (uint32_t j = 0, it = 0; j < n_queue_families; ++j) {
				if (n_queues_per_queue_family[j] > 0) {
					(*queue_create_infos)[it].sType =
						VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
					(*queue_create_infos)[it].pNext = RAW_NULL_PTR;
					(*queue_create_infos)[it].flags = 0;
					(*queue_create_infos)[it].queueFamilyIndex = j;
					(*queue_create_infos)[it].queueCount =
						n_queues_per_queue_family[j];
					(*queue_create_infos)[it].pQueuePriorities =
						*queue_priorities;

					++it;
				}
			}

			*physical_device_index = i;

			RAW_MEM_FREE(n_queues_per_queue_family);
			RAW_MEM_FREE(queue_families);
			RAW_MEM_FREE(device_extensions);

			return true;
		}

		RAW_MEM_FREE(n_queues_per_queue_family);
		RAW_MEM_FREE(queue_families);
		RAW_MEM_FREE(device_extensions);
	}

	return false;
}

