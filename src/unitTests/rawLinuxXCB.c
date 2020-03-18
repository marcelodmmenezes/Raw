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

/* Raw Rendering Engine - "src/unitTests/rawLinuxXCB.c"
 *
 * Unit testing procedures
 * Linux, XCB
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 18/03/2020
 */

#include <src/rawMemory.h>
#include <src/vulkan/rawVulkan.h>
#include <src/vulkan/rawVulkanInstance.h>

#include <assert.h>
#include <stdio.h>

void testMemoryAllocation() {
	puts("Running memory allocation test...");
	fflush(stdout);

	void* ptr = rawMemAlloc(4294967296);
	assert(ptr && "rawMemAlloc failed!");

	rawMemFree(ptr);
	ptr = RAW_NULL_PTR;
}

void testVulkanLibraryLoading() {
	puts("Running Vulkan library loading test...");
	fflush(stdout);

	RAW_VULKAN_LIBRARY vulkan;
	assert(rawLoadVulkan(vulkan) && "loadVulkan failed!");
}

void testVulkanInstanceCreationAndDestruction() {
	puts("Running Vulkan instance creation test...");
	fflush(stdout);

	VkExtensionProperties* available_extensions = RAW_NULL_PTR;
	uint32_t n_available_extensions;

	assert(rawEnumerateAvailableVulkanExtensions(
		available_extensions, &n_available_extensions) &&
		"Vulkan extension enumeration failed!");

	VkInstance instance = VK_NULL_HANDLE;

	char const* const* desired_extensions = RAW_NULL_PTR;
	uint32_t n_desired_extensions = 0;

	assert(rawCreateVulkanInstance(&instance, available_extensions,
		n_available_extensions, desired_extensions, n_desired_extensions,
		"rawLinuxXCB", VK_MAKE_VERSION(1, 0, 0)) &&
		"Vulkan instance creation failed!");

	assert(rawLoadVulkanInstanceLevelFunctions(
		instance, desired_extensions, n_desired_extensions) &&
		"rawLoadVulkanInstanceLevelFunctions failed!");

	rawDestroyVulkanInstance(&instance);

	assert(instance == VK_NULL_HANDLE &&
		"Vulkan instance destruction failed!");

	rawMemFree(available_extensions);
}

int main() {
	testMemoryAllocation();
	testVulkanLibraryLoading();
	testVulkanInstanceCreationAndDestruction();

	puts("All tests succeeded!");
}

