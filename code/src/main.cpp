
#include <cstdint>
#include <Drivers/stm32f042x6.h>
#include <Drivers/core_cm0.h>
#include <ufsel/bit_operations.hpp>

int main() {

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