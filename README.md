# MUL: Miles's Utility Library

A collection of utilities for debugging C programs.

- ANSI-escape sequence colors can be disabled by defining `MUL_COLOR_DISABLE` or used with the following macros:
	- `MUL_COLOR_BOLD`
	- `MUL_COLOR_RED`
	- `MUL_COLOR_GREEN`
	- `MUL_COLOR_YELLOW`
	- `MUL_COLOR_BLUE`
	- `MUL_COLOR_MAGENTA`
	- `MUL_COLOR_CYAN`
	- `MUL_COLOR_RESET`
- Logging can be disabled by defining `MUL_LOG_DISABLE` or used with the following function-like macro:
	- `MUL_LOG(message, ...)` (follows `printf()`-style formatting)
- Assertions can be disabled by defining `MUL_ASSERT_DISABLE` or used with the following function-like macro:
	- `MUL_ASSERT(condition, messsage, ...)` (follows `printf()`-style formatting)
- The "what-is" function-like macro is disabled if not compiling with GNU C or used with the following function-like macro:
	- `MUL_WHAT_IS(x)`
