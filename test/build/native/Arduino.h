/*
 * uuid-syslog - Microcontroller syslog service
 * Copyright 2022  Simon Arlott
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <unistd.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include <Print.h>
#include <Printable.h>
#include <Stream.h>
#include <WString.h>

#define PROGMEM
#define PGM_P const char *
#define PSTR(s) (__extension__({static const char __c[] = (s); &__c[0];}))

#define printf_P printf
#define strlen_P strlen
#define strncpy_P strncpy
#define strcmp_P strcmp

int snprintf_P(char *str, size_t size, const char *format, ...);
int vsnprintf_P(char *str, size_t size, const char *format, va_list ap);

#define pgm_read_byte(addr) (*reinterpret_cast<const char *>(addr))

class NativeConsole: public Print {
public:
	void begin(unsigned long baud __attribute__((unused))) {

	}

	size_t write(uint8_t c) override {
		return ::write(STDOUT_FILENO, &c, 1);
	}

	size_t write(const uint8_t *buffer, size_t size) {
		return ::write(STDOUT_FILENO, buffer, size);
	}
};

extern NativeConsole Serial;

unsigned long millis();

void delay(unsigned long millis);

void yield(void);

void setup(void);
void loop(void);

#endif
