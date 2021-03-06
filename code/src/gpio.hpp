
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

#include "pin.hpp"
#include <array>
#include <functional>

namespace gpio {

	namespace pins {

		//AIR1 je plus

		inline constexpr Pin P(char port, unsigned pin, Pin::Mode mode, Pin::Speed speed, Pin::Pull pull, unsigned char alternate_fun = 0) {
			std::uintptr_t ports[3] = {GPIOA_BASE,GPIOB_BASE, GPIOC_BASE};

			return Pin { ports[port - 'A'], uint16_t(1 << pin), mode, speed, pull, alternate_fun };
		}

		constexpr inline auto PWM_OUT = P('A', 7, Pin::Mode::alternatePP, Pin::Speed::fast, Pin::Pull::none, 4);

		constexpr inline auto LED_HIGHER = P('A', 3, Pin::Mode::outPP, Pin::Speed::slow, Pin::Pull::none);
		constexpr inline auto LED_LOWER = P('A', 4, Pin::Mode::outPP, Pin::Speed::slow, Pin::Pull::none);

		constexpr inline std::array all_pins{
			PWM_OUT,
		};
	}





	void Initialize(void);

	void InitializePin(Pin const& pin);


	void makeFloating(Pin const& pin);

}

#endif /*__GPIO_H */

/* END OF FILE */
