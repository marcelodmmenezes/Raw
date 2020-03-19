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

/* Raw Rendering Engine - "engine/utils/rawAssert.h"
 *
 * Assertion macros 
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 19/03/2020
 * Last modified: 19/03/2020
 */

#ifndef RAW_ASSERT_H
#define RAW_ASSERT_H

#include <engine/utils/rawLogger.h>

#include <stdlib.h>

#if defined (RAW_BUILD_DEBUG)
#define RAW_ASSERT(condition, message)          \
	if (!(condition)) {                         \
		RAW_LOG_ERROR("RAW_ASSERT: " #condition \
			"\n\t         " message);           \
		abort();                                \
	}
#else
#define RAW_ASSERT(condition, message)
#endif

#endif // RAW_ASSERT_H

