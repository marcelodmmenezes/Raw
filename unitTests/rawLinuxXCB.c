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
 * Last modified: 22/04/2020
 */

#include <unitTests/rawCrossPlatformTests.h>

#include <string.h>

// TODO: Create a usable window
void createXcbWindow(xcb_connection_t* connection, xcb_window_t* window) {
	xcb_screen_t* screen;

	connection = xcb_connect(RAW_NULL_PTR, RAW_NULL_PTR);

	RAW_ASSERT(!xcb_connection_has_error(connection),
		"Error connecting XCB!");

	screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
	*window = xcb_generate_id(connection);

	uint32_t event_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	uint32_t value_list[] = { screen->black_pixel, 0 };

	xcb_create_window(connection, XCB_COPY_FROM_PARENT,
		*window, screen->root, 0, 0, 800, 600, 0,
		XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
		event_mask, value_list);

	xcb_change_property(connection, XCB_PROP_MODE_REPLACE, *window,
		XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, strlen("rawLinuxXCB"),
		"rawLinuxXCB");

	xcb_map_window(connection, *window);
	RAW_ASSERT(xcb_flush(connection) > 0, "XCB flush error!");
}

void testVulkanPresentationSurfaceCreationAndDestruction(
	xcb_connection_t* connection,
	xcb_window_t window) {

	RAW_LOG_CMSG(RAW_LOG_BLUE,
		"Running RAW Vulkan presentation surface creation test...\n");

	RAW_VULKAN_LIBRARY vulkan = RAW_NULL_PTR;
	rawLoadVulkan(&vulkan);

	// Instance creation
	VkLayerProperties* available_instance_layers = RAW_NULL_PTR;
	uint32_t n_available_instance_layers;

	rawGetAvailableVulkanInstanceLayers(
		&available_instance_layers, &n_available_instance_layers);

	VkExtensionProperties* available_instance_extensions = RAW_NULL_PTR;
	uint32_t n_available_instance_extensions;

	rawGetAvailableVulkanInstanceExtensions(
		&available_instance_extensions, &n_available_instance_extensions);

	VkInstance instance = VK_NULL_HANDLE;

	char const* desired_instance_layers[] = {
		"VK_LAYER_KHRONOS_validation"
	};

	uint32_t n_desired_instance_layers = 1;

	char const* desired_instance_extensions[] = {
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
		VK_KHR_SURFACE_EXTENSION_NAME,
		RAW_VULKAN_PLATFORM_SURFACE_EXTENSION_NAME
	};

	uint32_t n_desired_instance_extensions = 3;

	bool result = rawCreateVulkanInstance(&instance,
		available_instance_layers, n_available_instance_layers,
		desired_instance_layers, n_desired_instance_layers,
		available_instance_extensions, n_available_instance_extensions,
		desired_instance_extensions, n_desired_instance_extensions,
		"rawLinuxXCB", VK_MAKE_VERSION(1, 0, 0));

	RAW_ASSERT(result, "rawCreateVulkanInstance failed");

	result = rawLoadVulkanInstanceLevelFunctions(
		instance, desired_instance_extensions, n_desired_instance_extensions);

	RAW_ASSERT(result, "rawLoadVulkanInstanceLevelFunctions failed");

	// Presentation surface creation
	VkSurfaceKHR presentation_surface;

	result = rawCreateVulkanPresentationSurface(
		instance, connection, window, &presentation_surface);

	RAW_ASSERT(result, "rawCreateVulkanPresentationSurface failed!");

	// Physical device creation and selection
	VkPhysicalDevice* physical_devices = RAW_NULL_PTR;
	uint32_t n_physical_devices;

	rawGetVulkanPhysicalDevices(
		instance, &physical_devices, &n_physical_devices);

	char const* desired_device_extensions[] = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	uint32_t n_desired_device_extensions = 1;

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

	uint32_t presentation_queue_index;
	uint32_t physical_device_index;

puts("Testing A");fflush(stdout);

uint32_t n_present_modes = 0u;
result = vkGetPhysicalDeviceSurfacePresentModesKHR(physical_devices[0],
	presentation_surface, &n_present_modes, RAW_NULL_PTR);
printf("%u %u\n", result, n_present_modes);fflush(stdout);
/*
uint32_t n_formats = 0u;
result = vkGetPhysicalDeviceSurfaceFormatsKHR(physical_devices[0],
	presentation_surface, &n_formats, RAW_NULL_PTR);
printf("%u %u\n", result, n_formats);fflush(stdout);
*/
/*
VkSurfaceCapabilitiesKHR capabilities;
result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_devices[0],
	presentation_surface, &capabilities);
printf("%u\n", result);fflush(stdout);
*/
/*
VkBool32 presentation_supported = VK_FALSE;
result = vkGetPhysicalDeviceSurfaceSupportKHR(physical_devices[0],
	0, presentation_surface, &presentation_supported);
printf("%u %u\n", result, presentation_supported);fflush(stdout);
*/

puts("Testing B");fflush(stdout);
	result = rawSelectVulkanPhysicalDeviceWithDesiredCharacteristics(
		physical_devices, n_physical_devices,
		desired_device_extensions, n_desired_device_extensions,
		&features, &properties,
		desired_queue_capabilities, n_desired_queue_capabilities,
		&queue_priorities, &n_queue_priorities,
		&queue_create_infos, &n_queue_create_infos,
		presentation_surface, &presentation_queue_index,
		&physical_device_index);
puts("Testing C");fflush(stdout);

	RAW_ASSERT(result,
		"rawSelectPhysicalDeviceWithDesiredCharacteristics failed!");

	RAW_LOG_INFO("Selecting physical device %d", physical_device_index);

	// Logical device creation
	VkDevice logical_device;

	rawCreateVulkanLogicalDevice(
		physical_devices[physical_device_index],
		queue_create_infos, n_queue_create_infos,
		desired_instance_layers, n_desired_instance_layers,
		desired_device_extensions, n_desired_device_extensions,
		&features, &logical_device);

	rawLoadVulkanDeviceLevelFunctions(logical_device,
		desired_device_extensions, n_desired_device_extensions);

	// Logical device destruction
	rawDestroyVulkanLogicalDevice(&logical_device);

	RAW_MEM_FREE(queue_create_infos);
	RAW_MEM_FREE(queue_priorities);
	RAW_MEM_FREE(physical_devices);
	
	// Presentation surface destruction
	rawDestroyVulkanPresentationSurface(instance, &presentation_surface);

	RAW_ASSERT(presentation_surface == VK_NULL_HANDLE,
		"Vulkan presentation surface destruction failed!");

	// Instance destruction
	rawDestroyVulkanInstance(&instance);

	RAW_MEM_FREE(available_instance_extensions);
	RAW_MEM_FREE(available_instance_layers);

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

