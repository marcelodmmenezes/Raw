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

/* Raw Rendering Engine - "engine/unitTests/rawLinuxXCB.c"
 *
 * Unit testing procedures
 * Linux, XCB
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 08/04/2020
 */

#include <unitTests/rawCrossPlatformTests.h>

// TODO: Create a usable window
void createXcbWindow(xcb_connection_t* connection, xcb_window_t* window) {
	xcb_screen_t* screen;

	connection = xcb_connect(RAW_NULL_PTR, RAW_NULL_PTR);
	screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
	*window = xcb_generate_id(connection);

	xcb_create_window(connection, XCB_COPY_FROM_PARENT,
		*window, screen->root, 0, 0, 800, 600, 1,
		XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, 0, 0);

	xcb_map_window(connection, *window);
	xcb_flush(connection);
}

void testVulkanPresentationSurfaceCreationAndDestruction(
	xcb_connection_t* connection,
	xcb_window_t window) {

	RAW_LOG_CMSG(RAW_LOG_BLUE,
		"Running RAW Vulkan presentation surface creation test...\n");

	RAW_VULKAN_LIBRARY vulkan = RAW_NULL_PTR;
	rawLoadVulkan(&vulkan);

	// Instance creation
	VkLayerProperties* available_layers = RAW_NULL_PTR;
	uint32_t n_available_layers;

	rawGetAvailableVulkanInstanceLayers(
		&available_layers, &n_available_layers);

	VkExtensionProperties* available_extensions = RAW_NULL_PTR;
	uint32_t n_available_extensions;

	rawGetAvailableVulkanInstanceExtensions(
		&available_extensions, &n_available_extensions);

	VkInstance instance = VK_NULL_HANDLE;

	// Testing with debug layers and debug extensions
	char const* desired_layers[1] = {
		"VK_LAYER_KHRONOS_validation"
	};

	uint32_t n_desired_layers = 1;

	char const* desired_extensions[] = {
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
		VK_KHR_SURFACE_EXTENSION_NAME,
		RAW_VULKAN_SURFACE_EXTENSION_NAME
	};

	uint32_t n_desired_extensions = 3;

	rawCreateVulkanInstance(&instance, available_layers,
		n_available_layers, desired_layers, n_desired_layers,
		available_extensions, n_available_extensions,
		desired_extensions, n_desired_extensions,
		"rawLinuxXCB", VK_MAKE_VERSION(1, 0, 0));

	rawLoadVulkanInstanceLevelFunctions(
		instance, desired_extensions, n_desired_extensions);

	// Physical device creation and selection
	VkPhysicalDevice* physical_devices = RAW_NULL_PTR;
	uint32_t n_physical_devices;

	rawGetVulkanPhysicalDevices(
		instance, &physical_devices, &n_physical_devices);

	char const** device_extensions = RAW_NULL_PTR;
	n_desired_extensions = 0;

	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceProperties properties;

	VkQueueFlags desired_queue_capabilities[] = {
		VK_QUEUE_GRAPHICS_BIT,
		VK_QUEUE_COMPUTE_BIT
	};

	uint32_t n_desired_queue_capabilities = 2;

	float* queue_priorities = RAW_NULL_PTR;
	uint32_t n_queue_priorities;

	VkDeviceQueueCreateInfo* queue_create_infos = RAW_NULL_PTR;
	uint32_t n_queue_create_infos;

	uint32_t physical_device_index;

	rawSelectVulkanPhysicalDeviceWithDesiredCharacteristics(
		physical_devices, n_physical_devices,
		device_extensions, n_desired_extensions,
		&features, &properties,
		desired_queue_capabilities, n_desired_queue_capabilities,
		&queue_priorities, &n_queue_priorities,
		&queue_create_infos, &n_queue_create_infos,
		&physical_device_index);

	RAW_LOG_INFO("Selecting physical device %d", physical_device_index);

	// Logical device creation
	VkDevice logical_device;

	rawCreateVulkanLogicalDevice(
		physical_devices[physical_device_index],
		queue_create_infos, n_queue_create_infos,
		desired_layers, n_desired_layers,
		device_extensions, n_desired_extensions,
		&features, &logical_device);

	rawLoadVulkanDeviceLevelFunctions(logical_device,
		device_extensions, n_desired_extensions);

	// Presentation surface creation
	VkSurfaceKHR presentation_surface;
	
	bool result = rawCreateVulkanPresentationSurface(
		instance, connection, window, &presentation_surface);

	RAW_ASSERT(result, "rawCreateVulkanPresentationSurface failed!");

	// Presentation surface destruction
	rawDestroyVulkanPresentationSurface(instance, &presentation_surface);

	RAW_ASSERT(presentation_surface == VK_NULL_HANDLE,
		"Vulkan presentation surface destruction failed!");

	// Logical device destruction
	rawDestroyVulkanLogicalDevice(&logical_device);

	RAW_MEM_FREE(queue_create_infos);
	RAW_MEM_FREE(queue_priorities);
	RAW_MEM_FREE(physical_devices);
	
	// Instance destruction
	rawDestroyVulkanInstance(&instance);

	RAW_MEM_FREE(available_extensions);
	RAW_MEM_FREE(available_layers);

	rawReleaseVulkan(&vulkan);

	RAW_LOG_CMSG(RAW_LOG_GREEN, "Test succeeded!\n\n");
}

int main() {
	testLoggingLibrary();
	testMemoryAllocation();
	testVulkanLibraryLoading();
	testVulkanInstanceCreationAndDestruction();
	testVulkanPhysicalDeviceCreationAndDestruction();
	testRawSelectPhysicalDeviceWithDesiredCharacteristics();
	testVulkanLogicalDeviceCreationAndDestruction();

	xcb_connection_t* connection = RAW_NULL_PTR;
	xcb_window_t window;

	createXcbWindow(connection, &window);
	testVulkanPresentationSurfaceCreationAndDestruction(connection, window);

	RAW_LOG_CMSG(RAW_LOG_GREEN, "All tests succeeded!\n");
}

