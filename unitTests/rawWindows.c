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

/* Raw Rendering Engine - "engine/unitTests/rawWindows.c"
 *
 * Windows unit testing procedures
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 20/03/2020
 * Last modified: 20/03/2020
 */

#include <unitTests/rawCrossPlatformTests.h>

int main() {
	testLoggingLibrary();
	testMemoryAllocation();
	testVulkanLibraryLoading();
	testVulkanInstanceCreationAndDestruction();
	testVulkanPhysicalDeviceCreationAndDestruction();
	testRawSelectPhysicalDeviceWithDesiredCharacteristics();
	testVulkanLogicalDeviceCreationAndDestruction();

	RAW_LOG_CMSG("All tests succeeded!\n", RAW_LOG_GREEN);
}

