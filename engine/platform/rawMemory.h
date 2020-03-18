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

/* Raw Rendering Engine - "engine/platform/rawMemory.h"
 *
 * Cross-platform memory allocation API
 *
 * TODO: Implement custom memory allocators
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 16/03/2020
 * Last modified: 18/03/2020
 */

#ifndef RAW_MEMORY_H
#define RAW_MEMORY_H

#include <inttypes.h>

// TODO: Implement log library
#include <stdio.h>

void rawMemAlloc(void** ptr, uint64_t size);
void rawMemFree(void* ptr);

#define RAW_MEM_ALLOC(ptr, size, file, line)                   \
	printf("\tAllocating %" PRIu64 " bytes for pointer: " #ptr \
		"\n\tFile: %s, Line: %d\n", (size), (file), (line));   \
	rawMemAlloc((void**)&(ptr), (size))

#define RAW_MEM_FREE(ptr, file, line)                \
	printf("\tFreeing pointer: " #ptr                \
		"\n\tFile: %s, Line: %d\n", (file), (line)); \
	rawMemFree((ptr))

#endif // RAW_MEMORY_H

