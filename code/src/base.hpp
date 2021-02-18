#pragma once

#include <cstdint>

extern volatile uint32_t SystemTicks;

inline uint32_t HAL_GetTick() {
	return SystemTicks;
}
