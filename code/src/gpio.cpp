

#include <Drivers/stm32f042x6.h>
#include "gpio.hpp"

#include <initializer_list>
#include <array>
#include <bit>
#include <algorithm>
#include <functional>
#include <ranges>

#include <ufsel/bit_operations.hpp>

namespace gpio {

	using namespace pins;

	void InitializePin(Pin const& pin) {
		using namespace ufsel;

		GPIO_TypeDef& port = *pin.gpio();
		unsigned pinIndex = std::countr_zero(pin.pin);

		bit::modify(std::ref(port.MODER), bit::bitmask_of_width(2), static_cast<int>(pin.mode_), 2 * pinIndex);
		bit::sliceable_reference{port.OTYPER}[pinIndex] = static_cast<int>(pin.mode_) > 16;
		bit::modify(std::ref(port.OSPEEDR), bit::bitmask_of_width(2), static_cast<int>(pin.speed_), 2 * pinIndex);
		bit::modify(std::ref(port.PUPDR), bit::bitmask_of_width(2), static_cast<int>(pin.pull_), 2 * pinIndex);

		bit::modify(std::ref(port.AFR[pinIndex / 8]), bit::bitmask_of_width(4), pin.alternate_, 4 * (pinIndex % 8));
	}

	void makeFloating(Pin const& pin) {
		Pin floating_pin = pin;
		floating_pin.mode_ = Pin::Mode::input;
		floating_pin.pull_ = Pin::Pull::none;

		InitializePin(floating_pin);
	}

	void Initialize(void)
	{
		using namespace ufsel;

		bit::set(std::ref(RCC->AHBENR), 
			RCC_AHBENR_GPIOAEN, //enable clock to GPIO{A, B}
			RCC_AHBENR_GPIOBEN
			);

		std::ranges::for_each(pins::all_pins, InitializePin);
	}
}


/* END OF FILE */
