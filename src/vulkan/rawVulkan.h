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

/* Raw Rendering Engine - "src/vulkan/rawVulkan.h"
 *
 * Vulkan runtime function loading
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 16/03/2020
 */

#ifndef RAW_VULKAN_H
#define RAW_VULKAN_H

#include <src/platform/rawOS.h>

#include <vulkan/vulkan.h>

#include <stdbool.h>

#define vkGetInstanceProcAddr \
	rawVkGetInstanceProcAddr
extern PFN_vkGetInstanceProcAddr
	vkGetInstanceProcAddr;

#define vkEnumerateInstanceExtensionProperties \
	rawVkEnumerateInstanceExtensionProperties
extern PFN_vkEnumerateInstanceExtensionProperties
	vkEnumerateInstanceExtensionProperties;

#define vkEnumerateInstanceLayerProperties \
	rawVkEnumerateInstanceLayerProperties
extern PFN_vkEnumerateInstanceLayerProperties
	vkEnumerateInstanceLayerProperties;

#define vkCreateInstance \
	rawVkCreateInstance
extern PFN_vkCreateInstance
	vkCreateInstance;

/*
 * Loads Vulkan runtime library, vkGetInstanceProcAddr
 * and Vulkan global level functions.
 */
bool rawLoadVulkan(RAW_VULKAN_LIBRARY vulkan);

#endif // RAW_VULKAN_H

