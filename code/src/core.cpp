#include "core.hpp"
#include <ufsel/bit_operations.hpp>
#include "assert.hpp"
#include <Drivers/stm32f042x6.h>
#include <bit>

namespace bsp::clock {

	namespace {
		/*Given the frequency of HSE and the desired sysclk frequency, calculate the PREDIV (frequency divider between
		HSE and PLL) and PLLMUL (multiplication coefficient of PLL) to achieve the desired sysclk frequency.*/
		constexpr std::pair<int, int> calculate_PREDIV1_PLLMUL(Frequency const hse, Frequency const sysclk) {
			constexpr std::array possible_pllmul{ 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
			constexpr std::array possible_prediv{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

			for (auto const div : possible_prediv)
				for (auto const mul : possible_pllmul) {
					auto const pllInput = hse / div;
					if (pllInput * div != hse)
						continue; //this divisor would lead to fractional frequency and I probably don't want that
					if (pllInput * mul == sysclk)
						return { div, mul };
				}
			return { 0,0 };

		}
	}

	void Initialize() {
		using namespace ufsel;

		SysTick->LOAD = SYSCLK / SYSTICK - 1;
		SysTick->VAL = 0; //clear the count register and the COUNT flag
		bit::set(std::ref(SysTick->CTRL),
			SysTick_CTRL_CLKSOURCE_Msk, //clock the systick from processor clock
			SysTick_CTRL_TICKINT_Msk, //enable the interrupt generation
			SysTick_CTRL_ENABLE_Msk //enable systick
		);

		constexpr auto prediv_pllmul = calculate_PREDIV1_PLLMUL(HSI, SYSCLK);
		static_assert(prediv_pllmul.first != 0 && prediv_pllmul.second != 0,
			"It is impossible to achieve the specified SYSCLK frequency using available PLL and prediv");

		constexpr unsigned PCLK_div = SYSCLK / APB;
		constexpr unsigned ADC_div = SYSCLK / ADC_freq;
		static_assert(PCLK_div * APB == SYSCLK, "Desired APB frequency is not a divisor of SYSCLK.");
		static_assert(ADC_div * ADC_freq == SYSCLK, "Desired ADC frequency is not a divisor of SYSCLK.");

		static_assert(std::has_single_bit(PCLK_div), "Peripheral prescaler must be a power of 2.");
		static_assert(ADC_div % 2 == 0, "ADC prescaler must be a multiple of 2.");

		static_assert(PCLK_div <= 16, "Peripheral prescaler must be at most 16.");
		static_assert(ADC_div >= 2 && ADC_div <= 8, "ADC prescaler must be at most 8, at least 2.");

		//configure the divider between HSE and PLL
		bit::sliceable_reference{RCC->CFGR2}[3_to, 0] = prediv_pllmul.first - 1;

		{
			bit::sliceable_with_deffered_writeback cfgr{ RCC->CFGR };

			//configure the PLL multiplier
			cfgr[21_to, 18] = prediv_pllmul.second - 2;
			//clock PLL from predived HSI
			cfgr[16_to, 15] = 0b01;
			//configure the ADC clock prescaler
			cfgr[15_to, 14] = std::countr_zero(ADC_div) - 1;
			//configure the clock prescaler for advanced peripheral bus 1
			cfgr[10_to, 8] = 3 + std::countr_zero(PCLK_div);
		}

		bit::set(std::ref(RCC->CR), RCC_CR_PLLON); //Enable PLL


		bit::wait_until_cleared(RCC->CR, RCC_CR_PLLRDY); //wait for PLL to settle

		bit::modify(std::ref(RCC->CFGR), RCC_CFGR_SW, 0b10); //Set PLL as system clock
		while (bit::sliceable_value{ RCC->CFGR } [3_to, 2] != 0b10); //wait for it settle.
	}
}

namespace bsp::reset {

	static ResetAgent reason = ResetAgent::unknown;


	ResetAgent readFlags() {
		std::uint32_t const reg{ RCC->CSR };

		constexpr std::pair<std::uint32_t, ResetAgent> flags[]{
			{RCC_CSR_LPWRRSTF, ResetAgent::lowPower},
			{RCC_CSR_WWDGRSTF, ResetAgent::windowWatchdog},
			{RCC_CSR_IWDGRSTF, ResetAgent::independentWatchdog},
			{RCC_CSR_SFTRSTF, ResetAgent::software},
			{RCC_CSR_PORRSTF, ResetAgent::powerOn},
			{RCC_CSR_PINRSTF, ResetAgent::pin}
		};

		for (auto const& [bitmask, reason] : flags)
			if (ufsel::bit::get(reg, bitmask))
				return reason;

		return ResetAgent::unknown;
	}

	void loadFlagsAndClearReg() {
		reason = readFlags();
		ufsel::bit::set(std::ref(RCC->CSR), RCC_CSR_RMVF); //clear all reset flags 
	}

	ResetAgent why() { return reason; }

	void resetSystem() {
		NVIC_SystemReset();
	}
}

