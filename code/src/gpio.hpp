
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

#include "pin.hpp"

namespace gpio {

	namespace pins {

		//AIR1 je plus

		inline constexpr Pin P(char port, unsigned pin, Pin::Mode mode, Pin::Speed speed, Pin::Pull pull) {
			std::uintptr_t ports[3] = {GPIOA_BASE,GPIOB_BASE, GPIOC_BASE};

			return Pin { ports[port - 'A'], uint16_t(1 << pin), mode, speed, pull };
		}



	}





	void Initialize(void);

	void InitializePin(Pin const& pin);



}

#endif /*__GPIO_H */

/* END OF FILE */
