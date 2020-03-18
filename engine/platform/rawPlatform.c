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

/* Raw Rendering Engine - "engine/platform/rawPlatform.c"
 *
 * Operating system abstraction API
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 18/03/2020
 * Last modified: 18/03/2020
 */

#include <engine/platform/rawPlatform.h>

///----------------------------------------------------------------------- LINUX
#include <stdio.h>

void rawPlatformSwitchTerminalColor(RawPlatformTerminalColor color) {
	switch (color) {
		case RAW_PLATFORM_TERMINAL_COLOR_RED:
			printf("\033[0;31m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_RED:
			printf("\033[1;31m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_GREEN:
			printf("\033[0;32m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_GREEN:
			printf("\033[1;32m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_YELLOW:
			printf("\033[0;33m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_YELLOW:
			printf("\033[1;33m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BLUE:
			printf("\033[0;34m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_BLUE:
			printf("\033[1;34m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_MAGENTA:
			printf("\033[0;35m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_MAGENTA:
			printf("\033[1;35m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_CYAN:
			printf("\033[0;36m");
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_CYAN:
			printf("\033[1;36m");
			break;

		default:
			printf("\033[0m");
	}
}

