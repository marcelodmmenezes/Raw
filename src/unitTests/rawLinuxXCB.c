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
 * Last modified: 16/03/2020
 */

#include <src/rawMemory.h>
#include <src/vulkan/rawVulkan.h>

#include <assert.h>
#include <stdio.h>

void testMemoryAllocation() {
	puts("Running memory allocation test...");

	void* ptr = rawMemAlloc(4294967296);
	assert(ptr && "rawMemAlloc failed!");

	rawMemFree(ptr);
	ptr = RAW_NULL_PTR;
}

void testVulkanLibraryLoading() {
	puts("Running vulkan library loading test...");

	VULKAN_LIBRARY vulkan;
	assert(loadVulkan(vulkan) && "loadVulkan failed!");
}

int main() {
	testMemoryAllocation();
	testVulkanLibraryLoading();
	puts("All tests succeeded!");
}

