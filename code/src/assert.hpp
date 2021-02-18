
#ifndef ASSERT_H
#define ASSERT_H

#include "options.hpp"

namespace diagnostics {
	[[noreturn]] void AssertionFailed_Handler();
}

inline bool assert_fun(const bool condition, const char* const where, const char* const func, int line) {
	if constexpr (enableAssert) {
		if (!condition) {
			debug_printf(("Assertion failed in %s:%d (function %s).\r\n", where, line, func));
			if constexpr (breakInFailedAssert)
				__asm("BKPT");
			diagnostics::AssertionFailed_Handler();
		}
	}
	return condition;
}



[[noreturn]]
inline void assert_unreachable_fun(const char * const where, const char * const func, int line) {
	if constexpr (enableAssert) {
		debug_printf(("Unreacheable point on %s:%d (function %s) reached!\r\n", where, line, func));
		if constexpr (breakInFailedAssert)
			__asm("BKPT");
	}
	diagnostics::AssertionFailed_Handler();
}

#define assert_unreachable() assert_unreachable_fun(__FILE__, __func__, __LINE__)
#define assert(cond) assert_fun(cond, __FILE__, __func__, __LINE__)



#endif
