#ifndef MUL_H
#define MUL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Misc.

#define MUL_STR_HELPER(x) #x
#define MUL_STR(x) MUL_STR_HELPER(x)
#define MUL_FILE_LINE_PREFIX "[" MUL_COLOR_BOLD __FILE__ ":" MUL_STR(__LINE__) MUL_COLOR_RESET "]"

// MUL_COLOR

#ifndef MUL_COLOR_DISABLE

#define MUL_COLOR_BOLD    "\x1b[1m"
#define MUL_COLOR_RED     "\x1b[31m"
#define MUL_COLOR_GREEN   "\x1b[32m"
#define MUL_COLOR_YELLOW  "\x1b[33m"
#define MUL_COLOR_BLUE    "\x1b[34m"
#define MUL_COLOR_MAGENTA "\x1b[35m"
#define MUL_COLOR_CYAN    "\x1b[36m"
#define MUL_COLOR_RESET   "\x1b[0m"

#else

#define MUL_COLOR_RED     ""
#define MUL_COLOR_GREEN   ""
#define MUL_COLOR_YELLOW  ""
#define MUL_COLOR_BLUE    ""
#define MUL_COLOR_MAGENTA ""
#define MUL_COLOR_CYAN    ""
#define MUL_COLOR_RESET   ""

#endif

// MUL_LOG

#ifndef MUL_LOG_DISABLE

#define MUL_LOG(message, ...) fprintf(stderr, MUL_FILE_LINE_PREFIX " " message "\n", ##__VA_ARGS__)

#else

#define MUL_LOG(message, ...) (void) 0

#endif

// MUL_ASSERT

#ifndef MUL_ASSERT_DISABLE

#define MUL_ASSERT(condition, message, ...) \
	((void) ((condition) || ( \
		fprintf(stderr, \
			MUL_FILE_LINE_PREFIX \
			" Assertion failed: " \
			MUL_COLOR_CYAN MUL_STR(condition) MUL_COLOR_RESET \
			", " MUL_COLOR_MAGENTA "\"" message "\"" MUL_COLOR_RESET "\n", \
			##__VA_ARGS__ \
		), \
		abort(), \
		0 \
	)))


#else

#define MUL_ASSERT(condition, message) (void) 0

#endif

// MUL_WHAT_IS

#ifdef __GNUC__

#define MUL_WHAT_IS(x) ({ \
	_Pragma("GCC diagnostic push"); \
	_Pragma("GCC diagnostic ignored \"-Wpointer-to-int-cast\""); \
	_Pragma("GCC diagnostic push"); \
	_Pragma("GCC diagnostic ignored \"-Wint-to-pointer-cast\""); \
	typeof(x) mul_x = x; \
	_Generic((mul_x), \
		bool:                 fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%s" MUL_COLOR_RESET "\n", (bool) (mul_x) ? "true" : "false"), \
		char:                 fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "'%c'" MUL_COLOR_RESET "\n", (char) (mul_x)), \
		double:               fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%lf" MUL_COLOR_RESET "\n", *(double *) (&mul_x)), \
		float:                fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%f" MUL_COLOR_RESET "\n", *(float *) (&mul_x)), \
		int:                  fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%d" MUL_COLOR_RESET "\n", (int) (mul_x)), \
		long long:            fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%lld" MUL_COLOR_RESET "\n", (long long) (mul_x)), \
		long:                 fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%ld" MUL_COLOR_RESET "\n", (long) (mul_x)), \
		short:                fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%hd" MUL_COLOR_RESET "\n", (short) mul_x), \
		signed char:          fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "'%c'" MUL_COLOR_RESET "\n", (signed char) (mul_x)), \
		unsigned char:        fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "'%c'" MUL_COLOR_RESET "\n", (unsigned char) (mul_x)), \
		unsigned long long:   fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%llu" MUL_COLOR_RESET "\n", (unsigned long long) (mul_x)), \
		unsigned long:        fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%lu" MUL_COLOR_RESET "\n", (unsigned long) (mul_x)), \
		unsigned short:       fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%hu" MUL_COLOR_RESET "\n", (unsigned short) mul_x), \
		unsigned:             fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%u" MUL_COLOR_RESET "\n", (unsigned) (mul_x)), \
		bool *:               fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		char *:               fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "\"%s\"" MUL_COLOR_RESET "\n", (char *) (uintptr_t) (mul_x)), \
		double *:             fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		float *:              fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		int *:                fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		long *:               fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		long long *:          fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		short *:              fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		signed char *:        fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		unsigned *:           fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		unsigned char *:      fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		unsigned long *:      fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		unsigned long long *: fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		unsigned short *:     fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		void *:               fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is " MUL_COLOR_MAGENTA "%p" MUL_COLOR_RESET "\n", (void *) (uintptr_t) (mul_x)), \
		default:              fprintf(stderr, MUL_FILE_LINE_PREFIX " " MUL_COLOR_CYAN MUL_STR(x) MUL_COLOR_RESET " is an unsupported type\n") \
	); \
	_Pragma("GCC diagnostic pop"); \
	_Pragma("GCC diagnostic pop"); \
})

#endif

#endif
