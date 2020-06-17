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
 * Last modified: 16/06/2020
 */

#ifndef RAW_VULKAN_PRESENTATION_H
#define RAW_VULKAN_PRESENTATION_H

#include <engine/platform/rawPlatform.h>
#include <engine/vulkan/rawVulkan.h>

#include <inttypes.h>
#include <stdbool.h>

/*
 * Creates Vulkan presentation surface
 * according to the platform
 */
bool rawCreateVulkanPresentationSurface(
	VkInstance instance,
	RAW_VULKAN_SURFACE_DISPLAY display,
	RAW_VULKAN_SURFACE_WINDOW window,
	VkSurfaceKHR* presentation_surface);

/*
 * If successful, the function will allocate memory for:
 *     @*present_modes
 *
 * It's the caller's responsibility to free that
 * memory through a call to RAW_MEM_FREE
 */
bool rawGetAvailableVulkanPresentModes(
	VkPhysicalDevice physical_device,
	VkSurfaceKHR presentation_surface,
	VkPresentModeKHR** present_modes,
	uint32_t* n_present_modes);

/*
 * If successful, the following parameters will be affected:
 *     @*n_swapchain_images:
 *                        will contain the number of
 *                        allocated swapchain images
 *     @*swapchain_width:
 *     @*swapchain_height:
 *                        if not 0 and the surface capabilities
 *                        extent is 0xFFFFFFFF, its values will
 *                        determine the dimensions of the swapchain.
 *                        if 0 and the surface capabilities
 *                        extent height is 0xFFFFFFF, the swapchain dimensions
 *                        will have the default value of 1024 x 768, and
 *                        these values will be stored on the parameters
 *                        otherwise the swapchain dimensions will be determined
 *                        by the surface capabilities, and the values will be
 *                        stored on the parameters
 *
 * If successful, this function will allocate memory for:
 *     @*swapchain_images
 *
 * It's the caller's responsibility to free that
 * memory through a call to RAW_MEM_FREE
 *
 * The swapchain image format is fixed for now
 * TODO: make swapchain image format dynamic
 */
bool rawCreateVulkanSwapchain(
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
	uint32_t* n_swapchain_images);

void rawDestroyVulkanSwapchain(
	VkDevice logical_device,
	VkSwapchainKHR* swapchain);

void rawDestroyVulkanPresentationSurface(
	VkInstance instance,
	VkSurfaceKHR* presentation_surface);

#endif // RAW_VULKAN_PRESENTATION_H

