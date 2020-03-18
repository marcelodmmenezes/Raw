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

/* Raw Rendering Engine - "src/vulkan/rawVulkanInstance.c"
 *
 * Vulkan instance related functions
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 18/03/2020
 */

#include <src/vulkan/rawVulkanInstance.h>
#include <src/rawMemory.h>

#include <assert.h>
#include <string.h>

// TODO: Implement log library
#include <stdio.h>

bool rawGetAvailableVulkanExtensions(
	VkExtensionProperties** available_extensions,
	uint32_t* n_extensions) {

	VkResult result = vkEnumerateInstanceExtensionProperties(
		RAW_NULL_PTR, n_extensions, RAW_NULL_PTR);

	if (result != VK_SUCCESS) {
		puts("ERROR: vkEnumerateInstanceExtensionProperties failed!");
		return false;
	}

	RAW_MEM_ALLOC(*available_extensions,
		*n_extensions * sizeof(VkExtensionProperties),
		__FILE__, __LINE__);

	if (!*available_extensions) {
		RAW_MEM_FREE(*available_extensions, __FILE__, __LINE__);
		*available_extensions = RAW_NULL_PTR;
		puts("ERROR: RAW_MEM_ALLOC failed on rawGetAvailableExtensions!");
		return false;
	}

	result = vkEnumerateInstanceExtensionProperties(
		RAW_NULL_PTR, n_extensions, *available_extensions);

	if (result != VK_SUCCESS) {
		RAW_MEM_FREE(*available_extensions, __FILE__, __LINE__);
		*available_extensions = RAW_NULL_PTR;
		puts("ERROR: vkEnumerateInstanceExtensionProperties failed!");
		return false;
	}

	return true;
}

bool rawCreateVulkanInstance(
	VkInstance* instance,
	VkExtensionProperties* const available_extensions,
	uint32_t n_available_extensions,
	char const* const* desired_extensions,
	uint32_t n_desired_extensions,
	char const* const application_name,
	uint32_t application_version) {

	for (uint32_t i = 0; i < n_desired_extensions; ++i) {
		bool available = false;

		for (uint32_t j = 0; j < n_available_extensions; ++j) {
			if (strstr(desired_extensions[i],
					available_extensions[j].extensionName)) {
				available = true;
				break;
			}
		}

		if (!available) {
			printf("ERROR: %s is not supported!", desired_extensions[i]);
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

	// TODO: Enable debug layers
	VkInstanceCreateInfo instance_create_info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = RAW_NULL_PTR,
		.flags = 0,
		.pApplicationInfo = &application_info,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = RAW_NULL_PTR,
		.enabledExtensionCount = n_desired_extensions,
		.ppEnabledExtensionNames = desired_extensions
	};

	// TODO: Pass allocation callback
	VkResult result = vkCreateInstance(
		&instance_create_info, RAW_NULL_PTR, instance);

	if ((result != VK_SUCCESS) || (*instance == VK_NULL_HANDLE)) {
		puts("ERROR: Vulkan instance creation failed!");
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
}

