
#include <cstdint>
#include <Drivers/stm32f042x6.h>
#include <Drivers/core_cm0.h>
#include <ufsel/bit_operations.hpp>

#include "gpio.hpp"
#include "timer.hpp"

std::optional<PWM_OUT> pwm;

int main() {
	using namespace ufsel;
	bit::set(std::ref(RCC->APB1ENR), RCC_APB1ENR_TIM14EN);
	pwm = PWM_OUT{TIM14};

	gpio::InitializePin(gpio::pins::LED_HIGHER);
	gpio::InitializePin(gpio::pins::LED_LOWER);


	for (unsigned i = 0;;++i) {
		switch (i % 4) {
		case 0:
			//First make the voltage accross LED zero by sending pin high
			gpio::InitializePin(gpio::pins::LED_HIGHER);
			gpio::pins::LED_HIGHER.Set();
			break;

		case 1:
			gpio::pins::LED_HIGHER.Clear(); //We apparently need to clear the pin's output to make it properly work
			//Then make both pins float, hence the LED sees 3R in series (smalles current)
			gpio::makeFloating(gpio::pins::LED_HIGHER);
			gpio::makeFloating(gpio::pins::LED_LOWER);
			break;
		case 2:
			//Then activate the lower pin and send it low. It now acts as a current sink for LED with 2R in series
			gpio::InitializePin(gpio::pins::LED_LOWER);
			gpio::pins::LED_LOWER.Clear();
			break;
		case 3:
			//Last activate the higher pins too and leave LED with a single R in series
			gpio::InitializePin(gpio::pins::LED_HIGHER);
			gpio::pins::LED_LOWER.Clear();
			break;
		}
		BlockingDelay(250_ms);
	}
}

extern "C" void SysTick_Handler(void)
{
	SystemTicks++;
	if (pwm.has_value()) {
		bool const subtract = SystemTicks & 512;
		unsigned const value = SystemTicks % 512;
		pwm->set_duty_cycle(subtract ? 512 - value : value); //50% percent is enough for full LED saturation
	}


	//TODO call something @ 1kHz
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
