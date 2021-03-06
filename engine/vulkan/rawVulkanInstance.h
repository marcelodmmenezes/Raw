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

/* Raw Rendering Engine - "engine/vulkan/rawVulkanInstance.h"
 *
 * Vulkan instance related functions
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 09/04/2020
 */

#ifndef RAW_VULKAN_INSTANCE_H
#define RAW_VULKAN_INSTANCE_H

#include <engine/vulkan/rawVulkan.h>

#include <inttypes.h>
#include <stdbool.h>

/*
 * If successful, the function will allocate memory for:
 *     @*available_layers
 *
 * It's the caller's responsibility to free that
 * memory through a call to RAW_MEM_FREE
 */
bool rawGetAvailableVulkanInstanceLayers(
	VkLayerProperties** available_layers,
	uint32_t* n_layers);

/*
 * If successful, the function will allocate memory for:
 *     @*available_extensions
 *
 * It's the caller's responsibility to free that
 * memory through a call to RAW_MEM_FREE
 */
bool rawGetAvailableVulkanInstanceExtensions(
	VkExtensionProperties** available_extensions,
	uint32_t* n_extensions);

/*
 * Creates the Vulkan instance only if all
 * desired_extensions are available.
 */
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
	uint32_t application_version,
	VkDebugUtilsMessengerCreateInfoEXT const* debug_create_info);

void rawDestroyVulkanInstance(VkInstance* instance);

#endif // RAW_VULKAN_INSTANCE_H

