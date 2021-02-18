
#include <cstdint>
#include <Drivers/stm32f042x6.h>
#include <Drivers/core_cm0.h>
#include <ufsel/bit_operations.hpp>

#include "gpio.hpp"
#include "timer.hpp"

int main() {

	bit::set(std::ref(RCC->APB1ENR), RCC_APB1ENR_TIM14EN);
	PWM_OUT pwm;

	for (unsigned i = 0;;++i) {
		gpio::pins::LED_A.Write(i & 1);
		gpio::pins::LED_B.Write(i & 2);
		pwm.set_duty_cycle(i * 5 % 100);
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