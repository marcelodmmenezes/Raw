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

/* Raw Rendering Engine - "engine/vulkan/rawVulkanPresentation.h"
 *
 * Vulkan logical device related functions
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 08/04/2020
 * Last modified: 26/05/2020
 */

#include <engine/vulkan/rawVulkanPresentation.h>
#include <engine/platform/rawMemory.h>
#include <engine/utils/rawLogger.h>

bool rawCreateVulkanPresentationSurface(
	VkInstance instance,
	RAW_VULKAN_SURFACE_DISPLAY display,
	RAW_VULKAN_SURFACE_WINDOW window,
	VkSurfaceKHR* presentation_surface) {

	RAW_VULKAN_SURFACE_CREATE_INFO surface_create_info = {
		.sType = RAW_VULKAN_SURFACE_CREATE_INFO_TYPE,
		.pNext = RAW_NULL_PTR,
		.flags = 0,
		.RAW_VULKAN_SURFACE_CREATION_PLATFORM_PARAMETER_1 = display,
		.RAW_VULKAN_SURFACE_CREATION_PLATFORM_PARAMETER_2 = window
	};

	// TODO: Pass allocation callback
	VkResult result = RAW_VULKAN_CREATE_SURFACE(instance,
		&surface_create_info, RAW_NULL_PTR, presentation_surface);

	if ((result != VK_SUCCESS) || (*presentation_surface == VK_NULL_HANDLE)) {
		RAW_LOG_ERROR("Vulkan presentation surface creation failed!");

		return false;
	}

	return true;
}

bool rawGetAvailableVulkanPresentModes(
	VkPhysicalDevice physical_device,
	VkSurfaceKHR presentation_surface,
	VkPresentModeKHR** present_modes,
	uint32_t* n_present_modes) {

	VkResult result = vkGetPhysicalDeviceSurfacePresentModesKHR(
		physical_device, presentation_surface,
		n_present_modes, RAW_NULL_PTR);

	if ((result != VK_SUCCESS) || (*n_present_modes == 0u)) {
		RAW_LOG_ERROR("vkGetPhysicalDeviceSurfacePresentModesKHR failed!");
		return false;
	}
	
	RAW_MEM_ALLOC(*present_modes, (uint64_t)*n_present_modes,
		sizeof(VkPresentModeKHR));

	if (!*present_modes) {
		RAW_LOG_ERROR("RAW_MEM_ALLOC failed on rawSelectVulkanPresentMode");
		return false;
	}

	result = vkGetPhysicalDeviceSurfacePresentModesKHR(
		physical_device, presentation_surface,
		n_present_modes, *present_modes);

	if ((result == VK_SUCCESS) || (!*present_modes)) {
		RAW_LOG_ERROR("vkGetPhysicalDeviceSurfacePresentModesKHR failed!");
		RAW_MEM_FREE(*present_modes);
		return false;
	}

	return true;
}

bool rawCreateSwapChain(
	VkPhysicalDevice physical_device,
	VkSurfaceKHR presentation_surface,
	VkPresentModeKHR desired_present_mode,
	VkImageUsageFlags desired_image_usage,
	VkSurfaceTransformFlagBitsKHR desired_transformation,
	uint32_t* n_swapchain_images,
	uint32_t* swapchain_width,
	uint32_t* swapchain_height) {

	VkPresentModeKHR* available_present_modes;
	uint32_t n_available_present_modes;

	if (!rawGetAvailableVulkanPresentModes(physical_device,
		presentation_surface, &available_present_modes,
		&n_available_present_modes)) {
		RAW_LOG_ERROR("rawGetAvailableVulkanPresentModes failed!");
		return false;
	}

	bool present_mode_supported = false;

	for (uint32_t i = 0; i < n_available_present_modes; ++i) {
		if (available_present_modes[i] == desired_present_mode) {
			present_mode_supported = true;
			break;
		}
	}

	RAW_MEM_FREE(available_present_modes);

	// TODO: Fallback to default present mode
	if (!present_mode_supported) {
		RAW_LOG_ERROR("Desired presentation mode is not supported!");
		return false;
	}

	VkSurfaceCapabilitiesKHR surface_capabilities;

	VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
		physical_device, presentation_surface, &surface_capabilities);

	if (result != VK_SUCCESS) {
		RAW_LOG_ERROR("Could not retrieve device surface capabilities!");
		return false;
	}

	if ((desired_image_usage & surface_capabilities.supportedUsageFlags)
		!= desired_image_usage) {
		RAW_LOG_ERROR("The surface doesn't support the desired image usage!");
		return false;
	}

	if ((desired_transformation & surface_capabilities.supportedTransforms)
		!= desired_transformation) {
		RAW_LOG_ERROR("The surface doesn't support "
			"the desired transformation!");
		return false;
	}

	*n_swapchain_images = surface_capabilities.minImageCount + 1u;

	if ((surface_capabilities.maxImageCount != 0) &&
		(*n_swapchain_images > surface_capabilities.maxImageCount))
		*n_swapchain_images = surface_capabilities.maxImageCount;

	VkExtent2D swapchain_size;

	if (surface_capabilities.currentExtent.width == 0xFFFFFFFF) {
		if (!swapchain_width)
			*swapchain_width = 1024u;

		swapchain_size.width = *swapchain_width;

		if (!swapchain_height)
			*swapchain_height = 768u;

		swapchain_size.height = *swapchain_height;

		/// Clamping the dimensions
		if (swapchain_size.width <
			surface_capabilities.minImageExtent.width)
			swapchain_size.width =
				surface_capabilities.minImageExtent.width;
		else if (swapchain_size.width >
			surface_capabilities.minImageExtent.width)
			swapchain_size.width =
				surface_capabilities.minImageExtent.width;

		if (swapchain_size.height <
			surface_capabilities.minImageExtent.height)
			swapchain_size.height =
				surface_capabilities.minImageExtent.height;
		else if (swapchain_size.height >
			surface_capabilities.minImageExtent.height)
			swapchain_size.height =
				surface_capabilities.minImageExtent.height;
	}
	else {
		swapchain_size = surface_capabilities.currentExtent;
		*swapchain_width = swapchain_size.width;
		*swapchain_height = swapchain_size.height;
	}

	return true;
}

void rawDestroyVulkanPresentationSurface(
	VkInstance instance,
	VkSurfaceKHR* presentation_surface) {

	if (presentation_surface) {
		// TODO: Pass allocation callback
		vkDestroySurfaceKHR(instance, *presentation_surface, RAW_NULL_PTR);
		*presentation_surface = VK_NULL_HANDLE;
	}
	else
		RAW_LOG_WARNING("Attempting to destroy "
			"NULL Vulkan presentation surface!");
}

