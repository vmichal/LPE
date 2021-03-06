

/* Includes -------------------------------------------------------------------*/
#include <Drivers/stm32f042x6.h>
#include <Drivers/core_cm0.h>
#include <ufsel/bit_operations.hpp>
#include "adc.hpp"
#include "gpio.hpp"
#include "timer.hpp"
#include "core.hpp"

#include <cstddef>

std::uint32_t volatile SystemTicks;

//Called immediatelly after reset (first executed instructions, .data and .bss are not yet initialized)
void SystemInit(void)
{
	//one wait state on flash accesses (SYSCLK is running at 48MHz)
	ufsel::bit::modify(std::ref(FLASH->ACR), ufsel::bit::bitmask_of_width(3), 0b01);
	bsp::clock::Initialize();
}

int main();

extern "C" {

	void Reset_Handler();
	void HardFault_Handler();
	__attribute__((weak, alias("HardFault_Handler"))) void NMI_Handler();
	__attribute__((weak, alias("HardFault_Handler"))) void SVC_Handler();
	__attribute__((weak, alias("HardFault_Handler"))) void PendSV_Handler();
	__attribute__((weak, alias("HardFault_Handler"))) void SysTick_Handler();
	__attribute__((weak, alias("HardFault_Handler"))) void WWDG_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void PVD_VDDIO2_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void RTC_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void FLASH_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void RCC_CRS_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void EXTI0_1_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void EXTI2_3_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void EXTI4_15_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void TSC_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void DMA1_Channel1_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void DMA1_Channel2_3_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void DMA1_Channel4_5_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void ADC1_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void TIM1_BRK_UP_TRG_COM_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void TIM1_CC_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void TIM2_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void TIM3_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void TIM14_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void TIM16_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void TIM17_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void SPI2_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void SPI1_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void USART1_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void USART2_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void I2C1_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void CEC_CAN_IRQHandler();
	__attribute__((weak, alias("HardFault_Handler"))) void USB_IRQHandler();

	extern std::uint32_t _estack[];

	using isr_routine = void(*)();

	__attribute__((section(".isr_vector"))) isr_routine interrupt_vector[]{
		reinterpret_cast<isr_routine>(_estack),
		Reset_Handler, // Reset Handler
		NMI_Handler, // NMI Handler
		HardFault_Handler, // Hard Fault Handler
		nullptr, // Reserved
		nullptr, // Reserved
		nullptr, // Reserved
		nullptr, // Reserved
		nullptr, // Reserved
		nullptr, // Reserved
		nullptr, // Reserved
		SVC_Handler, // SVCall Handler
		nullptr, // Reserved
		nullptr, // Reserved
		PendSV_Handler, // PendSV Handler
		SysTick_Handler, // SysTick Handler

		// External Interrupts
		WWDG_IRQHandler, // Window Watchdog
		PVD_VDDIO2_IRQHandler, // PVDand VDDIO2 through EXTI Line detect
		RTC_IRQHandler, // RTC through EXTI Line
		FLASH_IRQHandler, // FLASH
		RCC_CRS_IRQHandler, // RCCand CRS
		EXTI0_1_IRQHandler, // EXTI Line 0 and 1
		EXTI2_3_IRQHandler, // EXTI Line 2 and 3
		EXTI4_15_IRQHandler, // EXTI Line 4 to 15
		TSC_IRQHandler, // TSC
		DMA1_Channel1_IRQHandler, // DMA1 Channel 1
		DMA1_Channel2_3_IRQHandler, // DMA1 Channel 2 and Channel 3
		DMA1_Channel4_5_IRQHandler, // DMA1 Channel 4 and Channel 5
		ADC1_IRQHandler, // ADC1
		TIM1_BRK_UP_TRG_COM_IRQHandler, // TIM1 Break, Update, Triggerand Commutation
		TIM1_CC_IRQHandler, // TIM1 Capture Compare
		TIM2_IRQHandler, // TIM2
		TIM3_IRQHandler, // TIM3
		nullptr, // Reserved
		nullptr, // Reserved
		TIM14_IRQHandler, // TIM14
		nullptr, // Reserved
		TIM16_IRQHandler, // TIM16
		TIM17_IRQHandler, // TIM17
		I2C1_IRQHandler, // I2C1
		nullptr, // Reserved
		SPI1_IRQHandler, // SPI1
		SPI2_IRQHandler, // SPI2
		USART1_IRQHandler, // USART1
		USART2_IRQHandler, // USART2
		nullptr, // Reserved
		CEC_CAN_IRQHandler, // CECand CAN
		USB_IRQHandler, // USB
	};

	extern std::uint32_t _edata[], _sdata[], _load_data[];
	extern std::uint32_t _ebss[], _sbss[];
	extern void __libc_init_array();
	void Reset_Handler() {

		SystemInit();

		std::fill(_sbss, _ebss, 0); //clear .bss
		std::copy_n(_load_data, std::distance(_sdata, _edata), _sdata); //initialize .data

		__libc_init_array();

		using namespace ufsel;

		//From now on, the reset flags are accessible only whough the cached value (via function 'bsp::reset::why')
		//bsp::reset::loadFlagsAndClearReg();

		//MicrosecondTimer::Initialize();

		gpio::Initialize();

		//bsp::adc::Init();

		main();
	}

	void HardFault_Handler() {
		//Catches unimplemented interrupt requests, bus errors, usage errors...
		for (;;);
	}

}

