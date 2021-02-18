#pragma once

#include "options.hpp"
#include <ufsel/units.hpp>
#include "assert.hpp"

#include <array>
#include <cstdint>

namespace bsp::clock {

	//Frequencies of clocks and buses when the firmware is running normally
	constexpr auto HSE = 8_MHz;
	constexpr auto HSI = 8_MHz;
	constexpr auto SYSCLK = 48_MHz;
	constexpr auto APB = 48_MHz;
	constexpr auto ADC_freq = 12_MHz;
	constexpr auto SYSTICK = 1_kHz;

	void Initialize();
}

namespace bsp::reset {


	enum class ResetAgent {
		unknown,
		lowPower,
		windowWatchdog,
		independentWatchdog,
		software,
		powerOn,
		pin
	};

	void loadFlagsAndClearReg();
	ResetAgent why();
	ResetAgent readFlags();

	void resetSystem();

}


