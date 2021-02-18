
#include <cstdint>
#include <Drivers/stm32f042x6.h>
#include <Drivers/core_cm0.h>
#include <ufsel/bit_operations.hpp>

#include "gpio.hpp"
#include "timer.hpp"

int main() {
	for (unsigned i = 0;;++i) {
		gpio::pins::LED_A.Write(i & 1);
		gpio::pins::LED_B.Write(i & 2);
		BlockingDelay(250_ms);
	}
}

namespace diagnostics {

	[[noreturn]]
	void HardFault_Handler() {
		//TODO implement
		for (;;);
	}

	[[noreturn]]
	void AssertionFailedHandler() {
		HardFault_Handler();
	}
}