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

/* Raw Rendering Engine - "engine/vulkan/rawVulkan.h"
 *
 * Vulkan runtime function loading
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 23/05/2020
 */

#ifndef RAW_VULKAN_H
#define RAW_VULKAN_H

#include <engine/platform/rawPlatform.h>

#include <vulkan/vulkan.h>

#include <stdbool.h>

/*
 * Vulkan loader function
 */
#define vkGetInstanceProcAddr \
	rawVkGetInstanceProcAddr
extern PFN_vkGetInstanceProcAddr
	vkGetInstanceProcAddr;

/*
 * Vulkan global level functions
 */
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
 * Vulkan instance level functions
 */
#define vkEnumeratePhysicalDevices \
	rawVkEnumeratePhysicalDevices
extern PFN_vkEnumeratePhysicalDevices
	vkEnumeratePhysicalDevices;

#define vkEnumerateDeviceExtensionProperties \
	rawVkEnumerateDeviceExtensionProperties
extern PFN_vkEnumerateDeviceExtensionProperties
	vkEnumerateDeviceExtensionProperties;

#define vkEnumerateDeviceLayerProperties \
	rawVkEnumerateDeviceLayerProperties
extern PFN_vkEnumerateDeviceLayerProperties
	vkEnumerateDeviceLayerProperties;

#define vkGetPhysicalDeviceFeatures \
	rawVkGetPhysicalDeviceFeatures
extern PFN_vkGetPhysicalDeviceFeatures
	vkGetPhysicalDeviceFeatures;

#define vkGetPhysicalDeviceProperties \
	rawVkGetPhysicalDeviceProperties
extern PFN_vkGetPhysicalDeviceProperties
	vkGetPhysicalDeviceProperties;

#define vkGetPhysicalDeviceQueueFamilyProperties \
	rawVkGetPhysicalDeviceQueueFamilyProperties
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties
	vkGetPhysicalDeviceQueueFamilyProperties;

#define vkGetPhysicalDeviceMemoryProperties \
	rawVkGetPhysicalDeviceMemoryProperties
extern PFN_vkGetPhysicalDeviceMemoryProperties
	vkGetPhysicalDeviceMemoryProperties;

#define vkGetPhysicalDeviceFormatProperties \
	rawVkGetPhysicalDeviceFormatProperties
extern PFN_vkGetPhysicalDeviceFormatProperties
	vkGetPhysicalDeviceFormatProperties;

#define vkCreateDevice \
	rawVkCreateDevice
extern PFN_vkCreateDevice
	vkCreateDevice;

#define vkGetDeviceProcAddr \
	rawVkGetDeviceProcAddr
extern PFN_vkGetDeviceProcAddr
	vkGetDeviceProcAddr;

#define vkDestroyInstance \
	rawVkDestroyInstance
extern PFN_vkDestroyInstance
	vkDestroyInstance;

/*
 * Vulkan instance level extensions
 */
#define vkCreateDebugUtilsMessengerEXT \
 	rawVkCreateDebugUtilsMessengerEXT
extern PFN_vkCreateDebugUtilsMessengerEXT
	vkCreateDebugUtilsMessengerEXT;

#define vkDestroyDebugUtilsMessengerEXT \
	rawVkDestroyDebugUtilsMessengerEXT
extern PFN_vkDestroyDebugUtilsMessengerEXT
	vkDestroyDebugUtilsMessengerEXT;

#define vkGetPhysicalDeviceSurfaceSupportKHR \
	rawVkGetPhysicalDeviceSurfaceSupportKHR
extern PFN_vkGetPhysicalDeviceSurfaceSupportKHR
	vkGetPhysicalDeviceSurfaceSupportKHR;

#define vkGetPhysicalDeviceSurfaceCapabilitiesKHR \
	rawVkGetPhysicalDeviceSurfaceCapabilitiesKHR
extern PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR;

#define vkGetPhysicalDeviceSurfaceFormatsKHR \
	rawVkGetPhysicalDeviceSurfaceFormatsKHR
extern PFN_vkGetPhysicalDeviceSurfaceFormatsKHR
	vkGetPhysicalDeviceSurfaceFormatsKHR;

#define vkGetPhysicalDeviceSurfacePresentModesKHR \
	rawVkGetPhysicalDeviceSurfacePresentModesKHR
extern PFN_vkGetPhysicalDeviceSurfacePresentModesKHR
	vkGetPhysicalDeviceSurfacePresentModesKHR;

#define vkDestroySurfaceKHR \
	rawVkDestroySurfaceKHR
extern PFN_vkDestroySurfaceKHR
	vkDestroySurfaceKHR;

#if defined (RAW_PLATFORM_LINUX)
#if defined (RAW_PLATFORM_XCB_WINDOW_SYSTEM)
#define vkCreateXcbSurfaceKHR \
	rawVkCreateXcbSurfaceKHR
extern PFN_vkCreateXcbSurfaceKHR
	vkCreateXcbSurfaceKHR;
#endif
#elif defined (RAW_PLATFORM_WINDOWS)
#define vkCreateWin32SurfaceKHR \
	rawVkCreateWin32SurfaceKHR
extern PFN_vkCreateWin32SurfaceKHR
	vkCreateWin32SurfaceKHR;
#endif

/*
 * Vulkan device level functions
 */
#define vkGetDeviceQueue \
	rawVkGetDeviceQueue
extern PFN_vkGetDeviceQueue
	vkGetDeviceQueue;

#define vkDeviceWaitIdle \
	rawVkDeviceWaitIdle
extern PFN_vkDeviceWaitIdle
	vkDeviceWaitIdle;

#define vkDestroyDevice \
	rawVkDestroyDevice
extern PFN_vkDestroyDevice
	vkDestroyDevice;

#define vkCreateBuffer \
	rawVkCreateBuffer
extern PFN_vkCreateBuffer
	vkCreateBuffer;

#define vkGetBufferMemoryRequirements \
	rawVkGetBufferMemoryRequirements
extern PFN_vkGetBufferMemoryRequirements
	vkGetBufferMemoryRequirements;

#define vkAllocateMemory \
	rawVkAllocateMemory
extern PFN_vkAllocateMemory
	vkAllocateMemory;

#define vkBindBufferMemory \
	rawVkBindBufferMemory
extern PFN_vkBindBufferMemory
	vkBindBufferMemory;

#define vkCmdPipelineBarrier \
	rawVkCmdPipelineBarrier
extern PFN_vkCmdPipelineBarrier
	vkCmdPipelineBarrier;

#define vkCreateImage \
	rawVkCreateImage
extern PFN_vkCreateImage
	vkCreateImage;

#define vkGetImageMemoryRequirements \
	rawVkGetImageMemoryRequirements
extern PFN_vkGetImageMemoryRequirements
	vkGetImageMemoryRequirements;

#define vkBindImageMemory \
	rawVkBindImageMemory
extern PFN_vkBindImageMemory
	vkBindImageMemory;

#define vkCreateImageView \
	rawVkCreateImageView
extern PFN_vkCreateImageView
	vkCreateImageView;

#define vkMapMemory \
	rawVkMapMemory
extern PFN_vkMapMemory
	vkMapMemory;

#define vkFlushMappedMemoryRanges \
	rawVkFlushMappedMemoryRanges
extern PFN_vkFlushMappedMemoryRanges
	vkFlushMappedMemoryRanges;

#define vkUnmapMemory \
	rawVkUnmapMemory
extern PFN_vkUnmapMemory
	vkUnmapMemory;

#define vkCmdCopyBuffer \
	rawVkCmdCopyBuffer
extern PFN_vkCmdCopyBuffer
	vkCmdCopyBuffer;

#define vkCmdCopyBufferToImage \
	rawVkCmdCopyBufferToImage
extern PFN_vkCmdCopyBufferToImage
	vkCmdCopyBufferToImage;

#define vkCmdCopyImageToBuffer \
	rawVkCmdCopyImageToBuffer
extern PFN_vkCmdCopyImageToBuffer
	vkCmdCopyImageToBuffer;

#define vkBeginCommandBuffer \
	rawVkBeginCommandBuffer
extern PFN_vkBeginCommandBuffer
	vkBeginCommandBuffer;

#define vkEndCommandBuffer \
	rawVkEndCommandBuffer
extern PFN_vkEndCommandBuffer
	vkEndCommandBuffer;

#define vkQueueSubmit \
	rawVkQueueSubmit
extern PFN_vkQueueSubmit
	vkQueueSubmit;

#define vkDestroyImageView \
	rawVkDestroyImageView
extern PFN_vkDestroyImageView
	vkDestroyImageView;

#define vkDestroyImage \
	rawVkDestroyImage
extern PFN_vkDestroyImage
	vkDestroyImage;

#define vkDestroyBuffer \
	rawVkDestroyBuffer
extern PFN_vkDestroyBuffer
	vkDestroyBuffer;

#define vkFreeMemory \
	rawVkFreeMemory
extern PFN_vkFreeMemory
	vkFreeMemory;

#define vkCreateCommandPool \
	rawVkCreateCommandPool
extern PFN_vkCreateCommandPool
	vkCreateCommandPool;

#define vkAllocateCommandBuffers \
	rawVkAllocateCommandBuffers
extern PFN_vkAllocateCommandBuffers
	vkAllocateCommandBuffers;

#define vkCreateSemaphore \
	rawVkCreateSemaphore
extern PFN_vkCreateSemaphore
	vkCreateSemaphore;

#define vkCreateFence \
	rawVkCreateFence
extern PFN_vkCreateFence
	vkCreateFence;

#define vkWaitForFences \
	rawVkWaitForFences
extern PFN_vkWaitForFences
	vkWaitForFences;

#define vkResetFences \
	rawVkResetFences
extern PFN_vkResetFences
	vkResetFences;

#define vkDestroyFence \
	rawVkDestroyFence
extern PFN_vkDestroyFence
	vkDestroyFence;

#define vkDestroySemaphore \
	rawVkDestroySemaphore
extern PFN_vkDestroySemaphore
	vkDestroySemaphore;

#define vkResetCommandBuffer \
	rawVkResetCommandBuffer
extern PFN_vkResetCommandBuffer
	vkResetCommandBuffer;

#define vkFreeCommandBuffers \
	rawVkFreeCommandBuffers
extern PFN_vkFreeCommandBuffers
	vkFreeCommandBuffers;

#define vkResetCommandPool \
	rawVkResetCommandPool
extern PFN_vkResetCommandPool
	vkResetCommandPool;

#define vkDestroyCommandPool \
	rawVkDestroyCommandPool
extern PFN_vkDestroyCommandPool
	vkDestroyCommandPool;

#define vkCreateBufferView \
	rawVkCreateBufferView
extern PFN_vkCreateBufferView
	vkCreateBufferView;

#define vkDestroyBufferView \
	rawVkDestroyBufferView
extern PFN_vkDestroyBufferView
	vkDestroyBufferView;

#define vkQueueWaitIdle \
	rawVkQueueWaitIdle
extern PFN_vkQueueWaitIdle
	vkQueueWaitIdle;

#define vkCreateSampler \
	rawVkCreateSampler
extern PFN_vkCreateSampler
	vkCreateSampler;

#define vkCreateDescriptorSetLayout \
	rawVkCreateDescriptorSetLayout
extern PFN_vkCreateDescriptorSetLayout
	vkCreateDescriptorSetLayout;

#define vkCreateDescriptorPool \
	rawVkCreateDescriptorPool
extern PFN_vkCreateDescriptorPool
	vkCreateDescriptorPool;

#define vkAllocateDescriptorSets \
	rawVkAllocateDescriptorSets
extern PFN_vkAllocateDescriptorSets
	vkAllocateDescriptorSets;

#define vkUpdateDescriptorSets \
	rawVkUpdateDescriptorSets
extern PFN_vkUpdateDescriptorSets
	vkUpdateDescriptorSets;

#define vkCmdBindDescriptorSets \
	rawVkCmdBindDescriptorSets
extern PFN_vkCmdBindDescriptorSets
	vkCmdBindDescriptorSets;

#define vkFreeDescriptorSets \
	rawVkFreeDescriptorSets
extern PFN_vkFreeDescriptorSets
	vkFreeDescriptorSets;

#define vkResetDescriptorPool \
	rawVkResetDescriptorPool
extern PFN_vkResetDescriptorPool
	vkResetDescriptorPool;

#define vkDestroyDescriptorPool \
	rawVkDestroyDescriptorPool
extern PFN_vkDestroyDescriptorPool
	vkDestroyDescriptorPool;

#define vkDestroyDescriptorSetLayout \
	rawVkDestroyDescriptorSetLayout
extern PFN_vkDestroyDescriptorSetLayout
	vkDestroyDescriptorSetLayout;

#define vkDestroySampler \
	rawVkDestroySampler
extern PFN_vkDestroySampler
	vkDestroySampler;

#define vkCreateRenderPass \
	rawVkCreateRenderPass
extern PFN_vkCreateRenderPass
	vkCreateRenderPass;

#define vkCreateFramebuffer \
	rawVkCreateFramebuffer
extern PFN_vkCreateFramebuffer
	vkCreateFramebuffer;

#define vkDestroyFramebuffer \
	rawVkDestroyFramebuffer
extern PFN_vkDestroyFramebuffer
	vkDestroyFramebuffer;

#define vkDestroyRenderPass \
	rawVkDestroyRenderPass
extern PFN_vkDestroyRenderPass
	vkDestroyRenderPass;

#define vkCmdBeginRenderPass \
	rawVkCmdBeginRenderPass
extern PFN_vkCmdBeginRenderPass
	vkCmdBeginRenderPass;

#define vkCmdNextSubpass \
	rawVkCmdNextSubpass
extern PFN_vkCmdNextSubpass
	vkCmdNextSubpass;

#define vkCmdEndRenderPass \
	rawVkCmdEndRenderPass
extern PFN_vkCmdEndRenderPass
	vkCmdEndRenderPass;

#define vkCreatePipelineCache \
	rawVkCreatePipelineCache
extern PFN_vkCreatePipelineCache
	vkCreatePipelineCache;

#define vkGetPipelineCacheData \
	rawVkGetPipelineCacheData
extern PFN_vkGetPipelineCacheData
	vkGetPipelineCacheData;

#define vkMergePipelineCaches \
	rawVkMergePipelineCaches
extern PFN_vkMergePipelineCaches
	vkMergePipelineCaches;

#define vkDestroyPipelineCache \
	rawVkDestroyPipelineCache
extern PFN_vkDestroyPipelineCache
	vkDestroyPipelineCache;

#define vkCreateGraphicsPipelines \
	rawVkCreateGraphicsPipelines
extern PFN_vkCreateGraphicsPipelines
	vkCreateGraphicsPipelines;

#define vkCreateComputePipelines \
	rawVkCreateComputePipelines
extern PFN_vkCreateComputePipelines
	vkCreateComputePipelines;

#define vkDestroyPipeline \
	rawVkDestroyPipeline
extern PFN_vkDestroyPipeline
	vkDestroyPipeline;

#define vkDestroyEvent \
	rawVkDestroyEvent
extern PFN_vkDestroyEvent
	vkDestroyEvent;

#define vkDestroyQueryPool \
	rawVkDestroyQueryPool
extern PFN_vkDestroyQueryPool
	vkDestroyQueryPool;

#define vkCreateShaderModule \
	rawVkCreateShaderModule
extern PFN_vkCreateShaderModule
	vkCreateShaderModule;

#define vkDestroyShaderModule \
	rawVkDestroyShaderModule
extern PFN_vkDestroyShaderModule
	vkDestroyShaderModule;

#define vkCreatePipelineLayout \
	rawVkCreatePipelineLayout
extern PFN_vkCreatePipelineLayout
	vkCreatePipelineLayout;

#define vkDestroyPipelineLayout \
	rawVkDestroyPipelineLayout
extern PFN_vkDestroyPipelineLayout
	vkDestroyPipelineLayout;

#define vkCmdBindPipeline \
	rawVkCmdBindPipeline
extern PFN_vkCmdBindPipeline
	vkCmdBindPipeline;

#define vkCmdSetViewport \
	rawVkCmdSetViewport
extern PFN_vkCmdSetViewport
	vkCmdSetViewport;

#define vkCmdSetScissor \
	rawVkCmdSetScissor
extern PFN_vkCmdSetScissor
	vkCmdSetScissor;

#define vkCmdBindVertexBuffers \
	rawVkCmdBindVertexBuffers
extern PFN_vkCmdBindVertexBuffers
	vkCmdBindVertexBuffers;

#define vkCmdDraw \
	rawVkCmdDraw
extern PFN_vkCmdDraw
	vkCmdDraw;

#define vkCmdDrawIndexed \
	rawVkCmdDrawIndexed
extern PFN_vkCmdDrawIndexed
	vkCmdDrawIndexed;

#define vkCmdDispatch \
	rawVkCmdDispatch
extern PFN_vkCmdDispatch
	vkCmdDispatch;

#define vkCmdCopyImage \
	rawVkCmdCopyImage
extern PFN_vkCmdCopyImage
	vkCmdCopyImage;

#define vkCmdPushConstants \
	rawVkCmdPushConstants
extern PFN_vkCmdPushConstants
	vkCmdPushConstants;

#define vkCmdClearColorImage \
	rawVkCmdClearColorImage
extern PFN_vkCmdClearColorImage
	vkCmdClearColorImage;

#define vkCmdClearDepthStencilImage \
	rawVkCmdClearDepthStencilImage
extern PFN_vkCmdClearDepthStencilImage
	vkCmdClearDepthStencilImage;

#define vkCmdBindIndexBuffer \
	rawVkCmdBindIndexBuffer
extern PFN_vkCmdBindIndexBuffer
	vkCmdBindIndexBuffer;

#define vkCmdSetLineWidth \
	rawVkCmdSetLineWidth
extern PFN_vkCmdSetLineWidth
	vkCmdSetLineWidth;

#define vkCmdSetDepthBias \
	rawVkCmdSetDepthBias
extern PFN_vkCmdSetDepthBias
	vkCmdSetDepthBias;

#define vkCmdSetBlendConstants \
	rawVkCmdSetBlendConstants
extern PFN_vkCmdSetBlendConstants
	vkCmdSetBlendConstants;

#define vkCmdExecuteCommands \
	rawVkCmdExecuteCommands
extern PFN_vkCmdExecuteCommands
	vkCmdExecuteCommands;

#define vkCmdClearAttachments \
	rawVkCmdClearAttachments
extern PFN_vkCmdClearAttachments
	vkCmdClearAttachments;

/*
 * Vulkan device level extensions
 */
#define vkCreateSwapchainKHR \
 	rawVkCreateSwapchainKHR
extern PFN_vkCreateSwapchainKHR
	vkCreateSwapchainKHR;

#define vkGetSwapchainImagesKHR \
	rawVkGetSwapchainImagesKHR
extern PFN_vkGetSwapchainImagesKHR
	vkGetSwapchainImagesKHR;

#define vkAcquireNextImageKHR \
	rawVkAcquireNextImageKHR
extern PFN_vkAcquireNextImageKHR
	vkAcquireNextImageKHR;

#define vkQueuePresentKHR \
	rawVkQueuePresentKHR
extern PFN_vkQueuePresentKHR
	vkQueuePresentKHR;

#define vkDestroySwapchainKHR \
	rawVkDestroySwapchainKHR
extern PFN_vkDestroySwapchainKHR
	vkDestroySwapchainKHR;

/*
 * Loads Vulkan runtime library, vkGetInstanceProcAddr
 * and Vulkan global level functions.
 */
bool rawLoadVulkan(RAW_VULKAN_LIBRARY* vulkan);

/*
 * Loads Vulkan intance level functions and extensions.
 * All extensions required by the engine must be present on the hardware.
 */
bool rawLoadVulkanInstanceLevelFunctions(
	VkInstance instance,
	char const* const* enabled_extensions,
	uint32_t n_enabled_extensions,
	bool load_debug_layer);

/*
 * Loads Vulkan device level functions and extensions.
 * All extensions required by the engine must be present on the hardware.
 */
bool rawLoadVulkanDeviceLevelFunctions(
	VkDevice logical_device,
	char const* const* enabled_extensions,
	uint32_t n_enabled_extensions);

/*
 * Releases Vulkan runtime library
 */
void rawReleaseVulkan(RAW_VULKAN_LIBRARY* vulkan);

#endif // RAW_VULKAN_H

