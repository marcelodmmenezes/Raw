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
 * Last modified: 22/04/2020
 */

#include <engine/vulkan/rawVulkanPresentation.h>
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
	VkResult result = RAW_VULKAN_CREATE_SURFACE(instance, &surface_create_info,
		RAW_NULL_PTR, presentation_surface);

	if ((result != VK_SUCCESS) || (*presentation_surface == VK_NULL_HANDLE)) {
		RAW_LOG_ERROR("Vulkan presentation surface creation failed!");

		return false;
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

