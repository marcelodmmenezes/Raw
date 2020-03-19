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

/* Raw Rendering Engine - "engine/vulkan/rawVulkanPhysicalDevice.h"
 *
 * Vulkan physical device related functions
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 18/03/2020
 * Last modified: 19/03/2020
 */

#ifndef RAW_VULKAN_PHYSICAL_DEVICE_H
#define RAW_VULKAN_PHYSICAL_DEVICE_H

#include <engine/vulkan/rawVulkan.h>

#include <inttypes.h>

/*
 * If successful, the function will allocate memory for:
 *     @*available_devices
 *
 * It's the caller's responsibility to free that
 * memory through a call to RAW_MEM_FREE
 */
bool rawGetVulkanPhysicalDevices(
	VkInstance instance,
	VkPhysicalDevice** available_devices,
	uint32_t* n_available_devices);

/*
 * If successful, the function will allocate memory for:
 *     @*available_extensions
 *     @*queue_families
 *
 * It's the caller's responsibility to free that
 * memory through a call to RAW_MEM_FREE
 */
bool rawGetVulkanPhysicalDeviceCharacteristics(
	VkPhysicalDevice physical_device,
	VkExtensionProperties** available_extensions,
	uint32_t* n_available_extensions,
	VkPhysicalDeviceFeatures* features,
	VkPhysicalDeviceProperties* properties,
	VkQueueFamilyProperties** queue_families,
	uint32_t* n_queue_families);

/*
 * If successful, an index to a queue family with
 * the desired capabilities will be stored in parameter
 *     @*queue_family_index
 */
bool rawGetVulkanPhysicalDeviceQueueFamilyIndex(
	VkPhysicalDevice physical_device,
	VkQueueFamilyProperties const* const queue_families,
	uint32_t n_queue_families,
	VkQueueFlags desired_capabilities,
	uint32_t* queue_family_index);

/*
 * If successful, an index to the first physical device
 * in @available_devices that has the desired properties
 * will be stored in parameter
 *     @*physical_device_index
 *
 * If successful, the function will allocate memory for:
 *     @*queue_priorities
 *     @*queue_create_infos
 *
 * It's the caller's responsibility to free that
 * memory through a call to RAW_MEM_FREE
 *
 * TODO: Better selection of physical device
 * (consider device efficiency, for instance)
 */
bool rawSelectPhysicalDeviceWithDesiredCharacteristics(
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
	uint32_t* physical_device_index);

#endif // RAW_VULKAN_PHYSICAL_DEVICE_H

