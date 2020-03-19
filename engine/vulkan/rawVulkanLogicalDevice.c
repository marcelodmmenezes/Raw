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

/* Raw Rendering Engine - "engine/vulkan/rawVulkanLogicalDevice.h"
 *
 * Vulkan logical device related functions
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 19/03/2020
 * Last modified: 19/03/2020
 */

#include <engine/vulkan/rawVulkanLogicalDevice.h>
#include <engine/utils/rawLogger.h>
#include <engine/utils/rawAssert.h>

bool rawCreateVulkanLogicalDevice(
	VkPhysicalDevice physical_device,
	VkDeviceQueueCreateInfo const* const device_queues,
	uint32_t n_device_queues,
	char const* const* device_extensions,
	uint32_t n_device_extensions,
	VkPhysicalDeviceFeatures* device_features,
	VkDevice* logical_device) {

	// TODO: Enable debug layers
	VkDeviceCreateInfo device_create_info = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = RAW_NULL_PTR,
		.flags = 0,
		.queueCreateInfoCount = n_device_queues,
		.pQueueCreateInfos = device_queues,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = RAW_NULL_PTR,
		.enabledExtensionCount = n_device_extensions,
		.ppEnabledExtensionNames = device_extensions,
		.pEnabledFeatures = device_features
	};

	// TODO: Pass allocation callback
	VkResult result = vkCreateDevice(physical_device,
		&device_create_info, RAW_NULL_PTR, logical_device);

	if ((result != VK_SUCCESS) || (*logical_device == VK_NULL_HANDLE)) {
		RAW_LOG_ERROR("Vulkan logical device creation failed!");

		return false;
	}

	return true;
}

void rawDestroyVulkanLogicalDevice(VkDevice* logical_device) {
	RAW_ASSERT(false, "NOT IMPLEMENTED: vkDestroyDevice not loaded");

	if (*logical_device) {
		// TODO: Pass allocation callback
		//vkDestroyDevice(*logical_device, RAW_NULL_PTR);
		logical_device = VK_NULL_HANDLE;
	}
	else
		RAW_LOG_WARNING("Attempting to destroy "
			"NULL Vulkan logical device!");
}

