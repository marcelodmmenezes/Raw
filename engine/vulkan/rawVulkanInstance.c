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

/* Raw Rendering Engine - "engine/vulkan/rawVulkanInstance.c"
 *
 * Vulkan instance related functions
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 08/04/2020
 */

#include <engine/vulkan/rawVulkanInstance.h>
#include <engine/platform/rawMemory.h>
#include <engine/utils/rawLogger.h>

#include <string.h>

bool rawGetAvailableVulkanInstanceLayers(
	VkLayerProperties** available_layers,
	uint32_t* n_layers) {

	VkResult result = vkEnumerateInstanceLayerProperties(
		n_layers, RAW_NULL_PTR);

	if (result != VK_SUCCESS) {
		RAW_LOG_ERROR("vkEnumerateInstanceLayerProperties failed!");

		return false;
	}

	RAW_MEM_ALLOC(*available_layers, (uint64_t)*n_layers,
		sizeof(VkLayerProperties));

	if (!*available_layers) {
		RAW_LOG_ERROR("RAW_MEM_ALLOC failed on "
			"rawGetAvailableVulkanInstanceLayers");

		RAW_MEM_FREE(*available_layers);

		return false;
	}

	result = vkEnumerateInstanceLayerProperties(
		n_layers, *available_layers);

	if (result != VK_SUCCESS) {
		RAW_LOG_ERROR("vkEnumerateInstanceLayerProperties failed!");

		RAW_MEM_FREE(*available_layers);

		return false;
	}

	return true;
}

bool rawGetAvailableVulkanInstanceExtensions(
	VkExtensionProperties** available_extensions,
	uint32_t* n_extensions) {

	VkResult result = vkEnumerateInstanceExtensionProperties(
		RAW_NULL_PTR, n_extensions, RAW_NULL_PTR);

	if (result != VK_SUCCESS) {
		RAW_LOG_ERROR("vkEnumerateInstanceExtensionProperties failed!");

		return false;
	}

	RAW_MEM_ALLOC(*available_extensions, (uint64_t)*n_extensions,
		sizeof(VkExtensionProperties));

	if (!*available_extensions) {
		RAW_LOG_ERROR("RAW_MEM_ALLOC failed on "
			"rawGetAvailableVulkanInstanceExtensions!");

		RAW_MEM_FREE(*available_extensions);

		return false;
	}

	result = vkEnumerateInstanceExtensionProperties(
		RAW_NULL_PTR, n_extensions, *available_extensions);

	if (result != VK_SUCCESS) {
		RAW_LOG_ERROR("vkEnumerateInstanceExtensionProperties failed!");

		RAW_MEM_FREE(*available_extensions);

		return false;
	}

	return true;
}

bool rawCreateVulkanInstance(
	VkInstance* instance,
	VkLayerProperties const* const available_layers,
	uint32_t n_available_layers,
	char const* const* const desired_layers,
	uint32_t n_desired_layers,
	VkExtensionProperties const* const available_extensions,
	uint32_t n_available_extensions,
	char const* const* const desired_extensions,
	uint32_t n_desired_extensions,
	char const* const application_name,
	uint32_t application_version) {

	// Checking layers
	for (uint32_t i = 0; i < n_desired_layers; ++i) {
		bool available = false;

		for (uint32_t j = 0; j < n_available_layers; ++j) {
			if (strcmp(desired_layers[i],
					available_layers[j].layerName) == 0) {
				available = true;
				break;
			}
		}

		if (!available) {
			RAW_LOG_ERROR("%s is not available!", desired_layers[i]);

			return false;
		}
	}

	// Checking extensions
	for (uint32_t i = 0; i < n_desired_extensions; ++i) {
		bool available = false;

		for (uint32_t j = 0; j < n_available_extensions; ++j) {
			if (strcmp(desired_extensions[i],
					available_extensions[j].extensionName) == 0) {
				available = true;
				break;
			}
		}

		if (!available) {
			RAW_LOG_ERROR("%s is not supported!", desired_extensions[i]);

			return false;
		}
	}

	VkApplicationInfo application_info = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = RAW_NULL_PTR,
		.pApplicationName = application_name,
		.applicationVersion = application_version,
		.pEngineName = RAW_ENGINE_NAME,
		.engineVersion = RAW_ENGINE_VERSION,
		.apiVersion = RAW_VULKAN_VERSION
	};

	VkInstanceCreateInfo instance_create_info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = RAW_NULL_PTR,
		.flags = 0,
		.pApplicationInfo = &application_info,
		.enabledLayerCount = n_desired_layers,
		.ppEnabledLayerNames = desired_layers,
		.enabledExtensionCount = n_desired_extensions,
		.ppEnabledExtensionNames = desired_extensions
	};

	// TODO: Pass allocation callback
	VkResult result = vkCreateInstance(
		&instance_create_info, RAW_NULL_PTR, instance);

	if ((result != VK_SUCCESS) || (*instance == VK_NULL_HANDLE)) {
		RAW_LOG_ERROR("Vulkan instance creation failed!");

		return false;
	}

	return true;
}

void rawDestroyVulkanInstance(VkInstance* instance) {
	if (*instance) {
		// TODO: Pass allocation callback
		vkDestroyInstance(*instance, RAW_NULL_PTR);
		*instance = VK_NULL_HANDLE;
	}
	else
		RAW_LOG_WARNING("Attempting to destroy "
			"NULL Vulkan instance!");
}

