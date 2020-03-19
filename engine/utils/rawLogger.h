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

/* Raw Rendering Engine - "engine/utils/rawLogger.h"
 *
 * Basic logging utilities
 * TODO: add custom file options
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 18/03/2020
 * Last modified: 19/03/2020
 */

#ifndef RAW_LOG_H
#define RAW_LOG_H

#include <engine/platform/rawPlatform.h>

#include <stdio.h>

#define RAW_LOG_RED RAW_PLATFORM_TERMINAL_COLOR_RED
#define RAW_LOG_BOLD_RED RAW_PLATFORM_TERMINAL_COLOR_BOLD_RED
#define RAW_LOG_GREEN RAW_PLATFORM_TERMINAL_COLOR_GREEN
#define RAW_LOG_BOLD_GREEN RAW_PLATFORM_TERMINAL_COLOR_BOLD_GREEN
#define RAW_LOG_YELLOW RAW_PLATFORM_TERMINAL_COLOR_YELLOW
#define RAW_LOG_BOLD_YELLOW RAW_PLATFORM_TERMINAL_COLOR_BOLD_YELLOW
#define RAW_LOG_BLUE RAW_PLATFORM_TERMINAL_COLOR_BLUE
#define RAW_LOG_BOLD_BLUE RAW_PLATFORM_TERMINAL_COLOR_BOLD_BLUE
#define RAW_LOG_MAGENTA RAW_PLATFORM_TERMINAL_COLOR_MAGENTA
#define RAW_LOG_BOLD_MAGENTA RAW_PLATFORM_TERMINAL_COLOR_BOLD_MAGENTA
#define RAW_LOG_CYAN RAW_PLATFORM_TERMINAL_COLOR_CYAN
#define RAW_LOG_BOLD_CYAN RAW_PLATFORM_TERMINAL_COLOR_BOLD_CYAN
#define RAW_LOG_DEFAULT RAW_PLATFORM_TERMINAL_COLOR_DEFAULT

#if defined (RAW_ENABLE_LOG_MSG)
#define RAW_LOG_MSG(msg)                                 \
	{                                                    \
		rawPlatformSwitchTerminalColor(RAW_LOG_DEFAULT); \
		printf(msg);                                     \
	}

#define RAW_LOG_CMSG(msg, color)                         \
	{                                                    \
		rawPlatformSwitchTerminalColor(color);           \
		printf(msg);                                     \
		rawPlatformSwitchTerminalColor(RAW_LOG_DEFAULT); \
	}
#else
#define RAW_LOG_MSG(msg)
#define RAW_LOG_CMSG(msg, color)
#endif

#if defined (RAW_ENABLE_LOG_TRACE)
#define RAW_LOG_TRACE(...)                                                \
	{                                                                     \
		rawPlatformSwitchTerminalColor(RAW_LOG_DEFAULT);                  \
		printf("\n\tTRACE:   ");                                          \
		printf(__VA_ARGS__);                                              \
		printf("\n\t         FILE: %s | LINE: %d\n", __FILE__, __LINE__); \
	}
#else
#define LOG_TRACE(...)
#endif

#if defined (RAW_ENABLE_LOG_INFO)
#define RAW_LOG_INFO(...)                                                 \
	{                                                                     \
		rawPlatformSwitchTerminalColor(RAW_LOG_BLUE);                     \
		printf("\n\tINFO:    ");                                          \
		printf(__VA_ARGS__);                                              \
		printf("\n\t         FILE: %s | LINE: %d\n", __FILE__, __LINE__); \
	}
#else
#define LOG_INFO(...)
#endif

#if defined (RAW_ENABLE_LOG_WARNING)
#define RAW_LOG_WARNING(...)                                              \
	{                                                                     \
		rawPlatformSwitchTerminalColor(RAW_LOG_YELLOW);                   \
		printf("\n\tWARNING: ");                                          \
		printf(__VA_ARGS__);                                              \
		printf("\n\t         FILE: %s | LINE: %d\n", __FILE__, __LINE__); \
	}
#else
#define LOG_WARNING(...)
#endif

#if defined (RAW_ENABLE_LOG_ERROR)
#define RAW_LOG_ERROR(...)                                                \
	{                                                                     \
		rawPlatformSwitchTerminalColor(RAW_LOG_RED);                      \
		printf("\n\tERROR:   ");                                          \
		printf(__VA_ARGS__);                                              \
		printf("\n\t         FILE: %s | LINE: %d\n", __FILE__, __LINE__); \
	}
#else
#define LOG_ERROR(...)
#endif

#endif // RAW_LOG_H

