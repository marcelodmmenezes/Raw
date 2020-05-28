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
 * Last modified: 27/05/2020
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
	VkDevice logical_device,
	VkSurfaceKHR presentation_surface,
	VkPresentModeKHR desired_present_mode,
	VkImageUsageFlags desired_image_usage,
	VkSurfaceTransformFlagBitsKHR desired_transformation,
	uint32_t* swapchain_width,
	uint32_t* swapchain_height,
	VkSwapchainKHR* previous_swapchain,
	VkSwapchainKHR* current_swapchain,
	VkImage** swapchain_images,
	uint32_t* n_swapchain_images) {

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

	VkExtent2D image_size;

	if (surface_capabilities.currentExtent.width == 0xFFFFFFFF) {
		if (!swapchain_width)
			*swapchain_width = 1024u;

		image_size.width = *swapchain_width;

		if (!swapchain_height)
			*swapchain_height = 768u;

		image_size.height = *swapchain_height;

		/// Clamping the dimensions
		if (image_size.width <
			surface_capabilities.minImageExtent.width)
			image_size.width =
				surface_capabilities.minImageExtent.width;
		else if (image_size.width >
			surface_capabilities.minImageExtent.width)
			image_size.width =
				surface_capabilities.minImageExtent.width;

		if (image_size.height <
			surface_capabilities.minImageExtent.height)
			image_size.height =
				surface_capabilities.minImageExtent.height;
		else if (image_size.height >
			surface_capabilities.minImageExtent.height)
			image_size.height =
				surface_capabilities.minImageExtent.height;
	}
	else {
		image_size = surface_capabilities.currentExtent;
		*swapchain_width = image_size.width;
		*swapchain_height = image_size.height;
	}

	uint32_t n_formats;

	result = vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device,
		presentation_surface, &n_formats, RAW_NULL_PTR);

	if ((result != VK_SUCCESS) || (n_formats == 0u)) {
		RAW_LOG_ERROR("vkGetPhysicalDeviceSurfaceFormatsKHR failed!");
		return false;
	}

	VkSurfaceFormatKHR* surface_formats;

	RAW_MEM_ALLOC(surface_formats,
		(uint64_t)n_formats, sizeof(VkSurfaceFormatKHR));

	if (!surface_formats) {
		RAW_LOG_ERROR("RAW_MEM_ALLOC failed on rawCreateSwapchain");
		return false;
	}

	result = vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device,
		presentation_surface, &n_formats, surface_formats);

	if ((result != VK_SUCCESS) || (n_formats == 0u)) {
		RAW_LOG_ERROR("vkGetPhysicalDeviceSurfaceFormatsKHR failed!");
		RAW_MEM_FREE(surface_formats);
		return false;
	}

	// TODO: make generic choice
	int32_t surface_format_id = -1;

	for (uint32_t i = 0; i < n_formats; ++i) {
		if (surface_formats[i].format == VK_FORMAT_B8G8R8A8_SRGB &&
			surface_formats[i].colorSpace ==
				VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			surface_format_id = (int32_t)i;
			break;
		}
	}

	if (surface_format_id == -1) {
		RAW_LOG_ERROR("The required surface format is not present!");
		RAW_MEM_FREE(surface_formats);
		return false;
	}

	VkSwapchainCreateInfoKHR swapchain_create_info = {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.pNext = RAW_NULL_PTR,
		.flags = 0,
		.surface = presentation_surface,
		.minImageCount = *n_swapchain_images,
		.imageFormat = surface_formats[surface_format_id].format,
		.imageColorSpace = surface_formats[surface_format_id].colorSpace,
		.imageExtent = image_size,
		.imageArrayLayers = 1,
		.imageUsage = desired_image_usage,
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = RAW_NULL_PTR,
		.preTransform = desired_transformation,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = desired_present_mode,
		.clipped = VK_TRUE,
		.oldSwapchain = *previous_swapchain
	};

	RAW_MEM_FREE(surface_formats);

	// TODO: Pass allocation callback
	result = vkCreateSwapchainKHR(logical_device,
		&swapchain_create_info, RAW_NULL_PTR, current_swapchain);

	if ((result != VK_SUCCESS) || (*current_swapchain == VK_NULL_HANDLE)) {
		RAW_LOG_ERROR("Could not create swapchain!");
		return false;
	}

	if (*previous_swapchain != VK_NULL_HANDLE) {
		// TODO: Pass allocation callback
		vkDestroySwapchainKHR(logical_device,
			*previous_swapchain, RAW_NULL_PTR);
		*previous_swapchain = VK_NULL_HANDLE;
	}

	// TODO: Pass allocation callback
	result = vkGetSwapchainImagesKHR(logical_device,
		*current_swapchain, n_swapchain_images, RAW_NULL_PTR);

	if ((result != VK_SUCCESS) || (*n_swapchain_images == 0)) {
		RAW_LOG_ERROR("vkGetSwapchainImagesKHR failed!");
		return false;
	}

	RAW_MEM_ALLOC(*swapchain_images,
		(uint64_t)*n_swapchain_images, sizeof(VkImage));

	if (!*swapchain_images) {
		RAW_LOG_ERROR("RAW_MEM_ALLOC failed on raw CreateSwapchain!");
		return false;
	}

	result = vkGetSwapchainImagesKHR(logical_device,
		*current_swapchain, n_swapchain_images, *swapchain_images);

	if ((result != VK_SUCCESS) || (*n_swapchain_images == 0)) {
		RAW_LOG_ERROR("vkGetSwapchainImagesKHR failed!");
		RAW_MEM_FREE(*swapchain_images);
		return false;
	}

	return true;
}

void rawDestroyVulkanSwapchain(
	VkDevice logical_device,
	VkSwapchainKHR* swapchain) {

	if (swapchain) {
		// TODO: Pass allocation callback
		vkDestroySwapchainKHR(logical_device, *swapchain, RAW_NULL_PTR);
		*swapchain = VK_NULL_HANDLE;
	}
	else
		RAW_LOG_WARNING("Attempting to destroy "
			"NULL Vulkan swapchain!");
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

