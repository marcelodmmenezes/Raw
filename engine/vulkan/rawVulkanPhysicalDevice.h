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
 * Last modified: 18/03/2020
 */

#ifndef RAW_VULKAN_PHYSICAL_DEVICE_H
#define RAW_VULKAN_PHYSICAL_DEVICE_H

#include <engine/vulkan/rawVulkan.h>

#include <inttypes.h>

/*
 * If sucessfull, the function will allocate memory for:
 *     @*available_devices
 *
 * It's the caller's responsibility to free that
 * memory through a call to RAW_MEM_FREE
 */
bool rawGetPhysicalDevices(
	VkInstance instance,
	VkPhysicalDevice** available_devices,
	uint32_t* n_available_devices);

/*
 * If sucessfull, the function will allocate memory for:
 *     @*available_extensions
 *     @*queue_families
 *
 * It's the caller's responsibility to free that
 * memory through a call to RAW_MEM_FREE
 */
bool rawGetPhysicalDeviceCharacteristics(
	VkPhysicalDevice physical_device,
	VkExtensionProperties** available_extensions,
	uint32_t* n_available_extensions,
	VkPhysicalDeviceFeatures* features,
	VkPhysicalDeviceProperties* properties,
	VkQueueFamilyProperties** queue_families,
	uint32_t* n_queue_families);

/*
 * Returns an index to a queue family with
 * the desired capabilities.
 */
bool rawGetPhysicalDeviceQueueFamily(
	VkPhysicalDevice physical_device,
	VkQueueFamilyProperties* const queue_families,
	uint32_t n_queue_families,
	VkQueueFlags desired_capabilities,
	uint32_t* queue_family_index);

#endif // RAW_VULKAN_PHYSICAL_DEVICE_H

