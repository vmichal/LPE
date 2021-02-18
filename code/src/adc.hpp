
#ifndef ADC_H
#define ADC_H

#include <Drivers/stm32f042x6.h>

#include <ufsel/units.hpp>

namespace adc {

	//Integrated ADC has 12bit resultion and reference voltage 3.3 V
	constexpr Voltage Vdda = 3300_mV;
	constexpr int ConversionRange = 1 << 12;

	constexpr int regularConversionLength = 1;

	/* Defines names connecting the ADC channel to its measured signal. */
	enum class Channel {
		AmbientTemperature
	};


	void Init();

	/* Returns raw 16bit reading from given channel. */
	uint16_t ReadoutRaw(Channel ch);

	Temperature getAmbientTemperature();
}

#endif
