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

/* Raw Rendering Engine - "engine/vulkan/rawVulkan.c"
 *
 * Vulkan runtime function loading
 *
 * NOTE: The LOAD macro functions calls are passing another
 * macros as arguments. The argument macros are expanded only
 * inside the LOAD macro function definition, not on the call.
 * When used with operators # and ## inside the definition,
 * the parameter is also not expanded, giving the LOAD macro functions
 * the expected result.
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 23/05/2020
 */

#include <engine/vulkan/rawVulkan.h>
#include <engine/utils/rawLogger.h>

#include <string.h>

/*
 * Vulkan loader function
 */
PFN_vkGetInstanceProcAddr
	vkGetInstanceProcAddr;

/*
 * Vulkan global level functions
 */
PFN_vkEnumerateInstanceExtensionProperties
	vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties
	vkEnumerateInstanceLayerProperties;
PFN_vkCreateInstance
	vkCreateInstance;

/*
 * Vulkan instance level functions
 */
PFN_vkEnumeratePhysicalDevices
	vkEnumeratePhysicalDevices;
PFN_vkEnumerateDeviceExtensionProperties
	vkEnumerateDeviceExtensionProperties;
PFN_vkEnumerateDeviceLayerProperties
	vkEnumerateDeviceLayerProperties;
PFN_vkGetPhysicalDeviceFeatures
	vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceProperties
	vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties
	vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceMemoryProperties
	vkGetPhysicalDeviceMemoryProperties;
PFN_vkGetPhysicalDeviceFormatProperties
	vkGetPhysicalDeviceFormatProperties;
PFN_vkCreateDevice
	vkCreateDevice;
PFN_vkGetDeviceProcAddr
	vkGetDeviceProcAddr;
PFN_vkDestroyInstance
	vkDestroyInstance;

/*
 * Vulkan instance level extensions
 */
PFN_vkCreateDebugUtilsMessengerEXT
	vkCreateDebugUtilsMessengerEXT;
PFN_vkDestroyDebugUtilsMessengerEXT
	vkDestroyDebugUtilsMessengerEXT;
PFN_vkGetPhysicalDeviceSurfaceSupportKHR
	vkGetPhysicalDeviceSurfaceSupportKHR;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR
	vkGetPhysicalDeviceSurfaceFormatsKHR;
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR
	vkGetPhysicalDeviceSurfacePresentModesKHR;
PFN_vkDestroySurfaceKHR
	vkDestroySurfaceKHR;

#if defined (RAW_PLATFORM_LINUX)
#if defined (RAW_PLATFORM_XCB_WINDOW_SYSTEM)
PFN_vkCreateXcbSurfaceKHR
	vkCreateXcbSurfaceKHR;
#endif
#elif defined (RAW_PLATFORM_WINDOWS)
PFN_vkCreateWin32SurfaceKHR
	vkCreateWin32SurfaceKHR;
#endif

/*
 * Vulkan device level functions
 */
PFN_vkGetDeviceQueue
	vkGetDeviceQueue;
PFN_vkDeviceWaitIdle
	vkDeviceWaitIdle;
PFN_vkDestroyDevice
	vkDestroyDevice;
PFN_vkCreateBuffer
	vkCreateBuffer;
PFN_vkGetBufferMemoryRequirements
	vkGetBufferMemoryRequirements;
PFN_vkAllocateMemory
	vkAllocateMemory;
PFN_vkBindBufferMemory
	vkBindBufferMemory;
PFN_vkCmdPipelineBarrier
	vkCmdPipelineBarrier;
PFN_vkCreateImage
	vkCreateImage;
PFN_vkGetImageMemoryRequirements
	vkGetImageMemoryRequirements;
PFN_vkBindImageMemory
	vkBindImageMemory;
PFN_vkCreateImageView
	vkCreateImageView;
PFN_vkMapMemory
	vkMapMemory;
PFN_vkFlushMappedMemoryRanges
	vkFlushMappedMemoryRanges;
PFN_vkUnmapMemory
	vkUnmapMemory;
PFN_vkCmdCopyBuffer
	vkCmdCopyBuffer;
PFN_vkCmdCopyBufferToImage
	vkCmdCopyBufferToImage;
PFN_vkCmdCopyImageToBuffer
	vkCmdCopyImageToBuffer;
PFN_vkBeginCommandBuffer
	vkBeginCommandBuffer;
PFN_vkEndCommandBuffer
	vkEndCommandBuffer;
PFN_vkQueueSubmit
	vkQueueSubmit;
PFN_vkDestroyImageView
	vkDestroyImageView;
PFN_vkDestroyImage
	vkDestroyImage;
PFN_vkDestroyBuffer
	vkDestroyBuffer;
PFN_vkFreeMemory
	vkFreeMemory;
PFN_vkCreateCommandPool
	vkCreateCommandPool;
PFN_vkAllocateCommandBuffers
	vkAllocateCommandBuffers;
PFN_vkCreateSemaphore
	vkCreateSemaphore;
PFN_vkCreateFence
	vkCreateFence;
PFN_vkWaitForFences
	vkWaitForFences;
PFN_vkResetFences
	vkResetFences;
PFN_vkDestroyFence
	vkDestroyFence;
PFN_vkDestroySemaphore
	vkDestroySemaphore;
PFN_vkResetCommandBuffer
	vkResetCommandBuffer;
PFN_vkFreeCommandBuffers
	vkFreeCommandBuffers;
PFN_vkResetCommandPool
	vkResetCommandPool;
PFN_vkDestroyCommandPool
	vkDestroyCommandPool;
PFN_vkCreateBufferView
	vkCreateBufferView;
PFN_vkDestroyBufferView
	vkDestroyBufferView;
PFN_vkQueueWaitIdle
	vkQueueWaitIdle;
PFN_vkCreateSampler
	vkCreateSampler;
PFN_vkCreateDescriptorSetLayout
	vkCreateDescriptorSetLayout;
PFN_vkCreateDescriptorPool
	vkCreateDescriptorPool;
PFN_vkAllocateDescriptorSets
	vkAllocateDescriptorSets;
PFN_vkUpdateDescriptorSets
	vkUpdateDescriptorSets;
PFN_vkCmdBindDescriptorSets
	vkCmdBindDescriptorSets;
PFN_vkFreeDescriptorSets
	vkFreeDescriptorSets;
PFN_vkResetDescriptorPool
	vkResetDescriptorPool;
PFN_vkDestroyDescriptorPool
	vkDestroyDescriptorPool;
PFN_vkDestroyDescriptorSetLayout
	vkDestroyDescriptorSetLayout;
PFN_vkDestroySampler
	vkDestroySampler;
PFN_vkCreateRenderPass
	vkCreateRenderPass;
PFN_vkCreateFramebuffer
	vkCreateFramebuffer;
PFN_vkDestroyFramebuffer
	vkDestroyFramebuffer;
PFN_vkDestroyRenderPass
	vkDestroyRenderPass;
PFN_vkCmdBeginRenderPass
	vkCmdBeginRenderPass;
PFN_vkCmdNextSubpass
	vkCmdNextSubpass;
PFN_vkCmdEndRenderPass
	vkCmdEndRenderPass;
PFN_vkCreatePipelineCache
	vkCreatePipelineCache;
PFN_vkGetPipelineCacheData
	vkGetPipelineCacheData;
PFN_vkMergePipelineCaches
	vkMergePipelineCaches;
PFN_vkDestroyPipelineCache
	vkDestroyPipelineCache;
PFN_vkCreateGraphicsPipelines
	vkCreateGraphicsPipelines;
PFN_vkCreateComputePipelines
	vkCreateComputePipelines;
PFN_vkDestroyPipeline
	vkDestroyPipeline;
PFN_vkDestroyEvent
	vkDestroyEvent;
PFN_vkDestroyQueryPool
	vkDestroyQueryPool;
PFN_vkCreateShaderModule
	vkCreateShaderModule;
PFN_vkDestroyShaderModule
	vkDestroyShaderModule;
PFN_vkCreatePipelineLayout
	vkCreatePipelineLayout;
PFN_vkDestroyPipelineLayout
	vkDestroyPipelineLayout;
PFN_vkCmdBindPipeline
	vkCmdBindPipeline;
PFN_vkCmdSetViewport
	vkCmdSetViewport;
PFN_vkCmdSetScissor
	vkCmdSetScissor;
PFN_vkCmdBindVertexBuffers
	vkCmdBindVertexBuffers;
PFN_vkCmdDraw
	vkCmdDraw;
PFN_vkCmdDrawIndexed
	vkCmdDrawIndexed;
PFN_vkCmdDispatch
	vkCmdDispatch;
PFN_vkCmdCopyImage
	vkCmdCopyImage;
PFN_vkCmdPushConstants
	vkCmdPushConstants;
PFN_vkCmdClearColorImage
	vkCmdClearColorImage;
PFN_vkCmdClearDepthStencilImage
	vkCmdClearDepthStencilImage;
PFN_vkCmdBindIndexBuffer
	vkCmdBindIndexBuffer;
PFN_vkCmdSetLineWidth
	vkCmdSetLineWidth;
PFN_vkCmdSetDepthBias
	vkCmdSetDepthBias;
PFN_vkCmdSetBlendConstants
	vkCmdSetBlendConstants;
PFN_vkCmdExecuteCommands
	vkCmdExecuteCommands;
PFN_vkCmdClearAttachments
	vkCmdClearAttachments;

/*
 * Vulkan device level extensions
 */
PFN_vkCreateSwapchainKHR
	vkCreateSwapchainKHR;
PFN_vkGetSwapchainImagesKHR
	vkGetSwapchainImagesKHR;
PFN_vkAcquireNextImageKHR
	vkAcquireNextImageKHR;
PFN_vkQueuePresentKHR
	vkQueuePresentKHR;
PFN_vkDestroySwapchainKHR
	vkDestroySwapchainKHR;

bool rawLoadVulkan(RAW_VULKAN_LIBRARY* vulkan) {
	RAW_LOAD_VULKAN_LIBRARY(*vulkan);

	if (!(*vulkan)) {
		RAW_LOG_ERROR("Vulkan runtime library connection failed!");

		return false;
	}

	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)
		RAW_LOAD_LIBRARY_FUNCTION(*vulkan, "vkGetInstanceProcAddr");

	if (!vkGetInstanceProcAddr) {
		RAW_LOG_ERROR("vkGetInstanceProcAddr could not be loaded!");

		return false;
	}

#define LOAD(func)                                                 \
	func = (PFN_##func)vkGetInstanceProcAddr(RAW_NULL_PTR, #func); \
	                                                               \
	if (!func) {                                                   \
		RAW_LOG_ERROR(#func " could not be loaded!");              \
                                                                   \
		return false;                                              \
	}

	LOAD(vkEnumerateInstanceExtensionProperties);
	LOAD(vkEnumerateInstanceLayerProperties);
	LOAD(vkCreateInstance);
#undef LOAD

	return true;
}

bool rawLoadVulkanInstanceLevelFunctions(
	VkInstance instance,
	char const* const* enabled_extensions,
	uint32_t n_enabled_extensions,
	bool load_debug_layer) {

#define LOAD(func)                                             \
	func = (PFN_##func)vkGetInstanceProcAddr(instance, #func); \
                                                               \
	if (!func) {                                               \
		RAW_LOG_ERROR(#func " could not be loaded!");          \
                                                               \
		return false;                                          \
	}

	LOAD(vkEnumeratePhysicalDevices);
	LOAD(vkEnumerateDeviceExtensionProperties);
	LOAD(vkGetPhysicalDeviceFeatures);
	LOAD(vkGetPhysicalDeviceProperties);
	LOAD(vkGetPhysicalDeviceQueueFamilyProperties);
	LOAD(vkGetPhysicalDeviceMemoryProperties);
	LOAD(vkGetPhysicalDeviceFormatProperties);
	LOAD(vkCreateDevice);
	LOAD(vkGetDeviceProcAddr);
	LOAD(vkDestroyInstance);
#undef LOAD

	bool extension_enabled;

#define LOAD(func, extension)                                          \
	extension_enabled = false;                                         \
                                                                       \
	for (uint32_t i = 0; i < n_enabled_extensions; ++i) {              \
		if (strcmp(enabled_extensions[i], extension) == 0) {           \
			extension_enabled = true;                                  \
                                                                       \
			func = (PFN_##func)vkGetInstanceProcAddr(instance, #func); \
                                                                       \
			if (!func) {                                               \
				RAW_LOG_ERROR(#func " could not be loaded!");          \
                                                                       \
				return false;                                          \
			}                                                          \
		}                                                              \
	}                                                                  \
                                                                       \
	if (!extension_enabled) {                                          \
		RAW_LOG_ERROR("Required extension " #extension                 \
			" was not enabled!");                                      \
			                                                           \
		return false;                                                  \
	}

	if (load_debug_layer) {
		LOAD(vkCreateDebugUtilsMessengerEXT,
			VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		LOAD(vkDestroyDebugUtilsMessengerEXT,
			VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	LOAD(vkGetPhysicalDeviceSurfaceSupportKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);
	LOAD(vkGetPhysicalDeviceSurfaceCapabilitiesKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);
	LOAD(vkGetPhysicalDeviceSurfaceFormatsKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);
	LOAD(vkGetPhysicalDeviceSurfacePresentModesKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);
	LOAD(vkDestroySurfaceKHR,
		VK_KHR_SURFACE_EXTENSION_NAME);

#if defined (RAW_PLATFORM_LINUX)
#if defined (RAW_PLATFORM_XCB_WINDOW_SYSTEM)
	LOAD(vkCreateXcbSurfaceKHR,
		RAW_VULKAN_PLATFORM_SURFACE_EXTENSION_NAME);
#endif
#endif
#undef LOAD

	return true;
}

bool rawLoadVulkanDeviceLevelFunctions(
	VkDevice logical_device,
	char const* const* enabled_extensions,
	uint32_t n_enabled_extensions) {

#define LOAD(func)                                                 \
	func = (PFN_##func)vkGetDeviceProcAddr(logical_device, #func); \
                                                                   \
	if (!func) {                                                   \
		RAW_LOG_ERROR(#func " could not be loaded!");              \
                                                                   \
		return false;                                              \
	}

	LOAD(vkGetDeviceQueue);
	LOAD(vkDeviceWaitIdle);
	LOAD(vkDestroyDevice);
	LOAD(vkCreateBuffer);
	LOAD(vkGetBufferMemoryRequirements);
	LOAD(vkAllocateMemory);
	LOAD(vkBindBufferMemory);
	LOAD(vkCmdPipelineBarrier);
	LOAD(vkCreateImage);
	LOAD(vkGetImageMemoryRequirements);
	LOAD(vkBindImageMemory);
	LOAD(vkCreateImageView);
	LOAD(vkMapMemory);
	LOAD(vkFlushMappedMemoryRanges);
	LOAD(vkUnmapMemory);
	LOAD(vkCmdCopyBuffer);
	LOAD(vkCmdCopyBufferToImage);
	LOAD(vkCmdCopyImageToBuffer);
	LOAD(vkBeginCommandBuffer);
	LOAD(vkEndCommandBuffer);
	LOAD(vkQueueSubmit);
	LOAD(vkDestroyImageView);
	LOAD(vkDestroyImage);
	LOAD(vkDestroyBuffer);
	LOAD(vkFreeMemory);
	LOAD(vkCreateCommandPool);
	LOAD(vkAllocateCommandBuffers);
	LOAD(vkCreateSemaphore);
	LOAD(vkCreateFence);
	LOAD(vkWaitForFences);
	LOAD(vkResetFences);
	LOAD(vkDestroyFence);
	LOAD(vkDestroySemaphore);
	LOAD(vkResetCommandBuffer);
	LOAD(vkFreeCommandBuffers);
	LOAD(vkResetCommandPool);
	LOAD(vkDestroyCommandPool);
	LOAD(vkCreateBufferView);
	LOAD(vkDestroyBufferView);
	LOAD(vkQueueWaitIdle);
	LOAD(vkCreateSampler);
	LOAD(vkCreateDescriptorSetLayout);
	LOAD(vkCreateDescriptorPool);
	LOAD(vkAllocateDescriptorSets);
	LOAD(vkUpdateDescriptorSets);
	LOAD(vkCmdBindDescriptorSets);
	LOAD(vkFreeDescriptorSets);
	LOAD(vkResetDescriptorPool);
	LOAD(vkDestroyDescriptorPool);
	LOAD(vkDestroyDescriptorSetLayout);
	LOAD(vkDestroySampler);
	LOAD(vkCreateRenderPass);
	LOAD(vkCreateFramebuffer);
	LOAD(vkDestroyFramebuffer);
	LOAD(vkDestroyRenderPass);
	LOAD(vkCmdBeginRenderPass);
	LOAD(vkCmdNextSubpass);
	LOAD(vkCmdEndRenderPass);
	LOAD(vkCreatePipelineCache);
	LOAD(vkGetPipelineCacheData);
	LOAD(vkMergePipelineCaches);
	LOAD(vkDestroyPipelineCache);
	LOAD(vkCreateGraphicsPipelines);
	LOAD(vkCreateComputePipelines);
	LOAD(vkDestroyPipeline);
	LOAD(vkDestroyEvent);
	LOAD(vkDestroyQueryPool);
	LOAD(vkCreateShaderModule);
	LOAD(vkDestroyShaderModule);
	LOAD(vkCreatePipelineLayout);
	LOAD(vkDestroyPipelineLayout);
	LOAD(vkCmdBindPipeline);
	LOAD(vkCmdSetViewport);
	LOAD(vkCmdSetScissor);
	LOAD(vkCmdBindVertexBuffers);
	LOAD(vkCmdDraw);
	LOAD(vkCmdDrawIndexed);
	LOAD(vkCmdDispatch);
	LOAD(vkCmdCopyImage);
	LOAD(vkCmdPushConstants);
	LOAD(vkCmdClearColorImage);
	LOAD(vkCmdClearDepthStencilImage);
	LOAD(vkCmdBindIndexBuffer);
	LOAD(vkCmdSetLineWidth);
	LOAD(vkCmdSetDepthBias);
	LOAD(vkCmdSetBlendConstants);
	LOAD(vkCmdExecuteCommands);
	LOAD(vkCmdClearAttachments);
#undef LOAD

	bool extension_enabled;

#define LOAD(func, extension)                                              \
	extension_enabled = false;                                             \
                                                                           \
	for (uint32_t i = 0; i < n_enabled_extensions; ++i) {                  \
		if (strcmp(enabled_extensions[i], extension) == 0) {               \
			extension_enabled = true;                                      \
                                                                           \
			func = (PFN_##func)vkGetDeviceProcAddr(logical_device, #func); \
                                                                           \
			if (!func) {                                                   \
				RAW_LOG_ERROR(#func " could not be loaded!");              \
                                                                           \
				return false;                                              \
			}                                                              \
		}                                                                  \
	}                                                                      \
                                                                           \
	if (!extension_enabled) {                                              \
		RAW_LOG_ERROR("Required extension " #extension                     \
			" was not enabled!");                                          \
			                                                               \
		return false;                                                      \
	}

	LOAD(vkCreateSwapchainKHR,
		VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	LOAD(vkGetSwapchainImagesKHR,
		VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	LOAD(vkAcquireNextImageKHR,
		VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	LOAD(vkQueuePresentKHR,
		VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	LOAD(vkDestroySwapchainKHR,
		VK_KHR_SWAPCHAIN_EXTENSION_NAME);
#undef LOAD

	return true;
}

void rawReleaseVulkan(RAW_VULKAN_LIBRARY* vulkan) {
	if (*vulkan) {
		RAW_RELEASE_VULKAN_LIBRARY(*vulkan);
		*vulkan = RAW_NULL_PTR;
	}
	else
		RAW_LOG_WARNING("Attempting to release "
			"NULL Vulkan library!");
}

