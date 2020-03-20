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

/* Raw Rendering Engine - "engine/platform/windows/rawPlatform.c"
 *
 * Operating system abstraction API
 *
 * Marcelo de Matos Menezes - marcelodmmenezes@gmail.com
 * Created: 20/03/2020
 * Last modified: 20/03/2020
 */

#include <engine/platform/rawPlatform.h>

#include <stdio.h>

void rawPlatformSwitchTerminalColor(RawPlatformTerminalColor color) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (color) {
		case RAW_PLATFORM_TERMINAL_COLOR_RED:
			SetConsoleTextAttribute(console, FOREGROUND_RED);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_RED:
			SetConsoleTextAttribute(console, BACKGROUND_RED);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_GREEN:
			SetConsoleTextAttribute(console, FOREGROUND_GREEN);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_GREEN:
			SetConsoleTextAttribute(console, BACKGROUND_GREEN);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_YELLOW:
			SetConsoleTextAttribute(console,
				FOREGROUND_RED | FOREGROUND_GREEN);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_YELLOW:
			SetConsoleTextAttribute(console,
				BACKGROUND_RED | BACKGROUND_GREEN);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BLUE:
			SetConsoleTextAttribute(console, FOREGROUND_BLUE);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_BLUE:
			SetConsoleTextAttribute(console, BACKGROUND_BLUE);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_MAGENTA:
			SetConsoleTextAttribute(console,
				FOREGROUND_RED | FOREGROUND_BLUE);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_MAGENTA:
			SetConsoleTextAttribute(console,
				BACKGROUND_RED | BACKGROUND_BLUE);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_CYAN:
			SetConsoleTextAttribute(console,
				FOREGROUND_GREEN | FOREGROUND_BLUE);
			break;

		case RAW_PLATFORM_TERMINAL_COLOR_BOLD_CYAN:
			SetConsoleTextAttribute(console,
				BACKGROUND_GREEN | BACKGROUND_BLUE);
			break;

		default:
			SetConsoleTextAttribute(console,
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}

