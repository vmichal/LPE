
#include <cstdint>
#include <Drivers/stm32f042x6.h>
#include <Drivers/core_cm0.h>

extern "C" {

	extern "C" void Reset_Handler();
	extern "C" void NMI_Handler();
	extern "C" void HardFault_Handler();
	extern "C" void SVC_Handler();
	extern "C" void PendSV_Handler();
	extern "C" void SysTick_Handler();
	extern "C" void WWDG_IRQHandler();
	extern "C" void PVD_VDDIO2_IRQHandler();
	extern "C" void RTC_IRQHandler();
	extern "C" void FLASH_IRQHandler();
	extern "C" void RCC_CRS_IRQHandler();
	extern "C" void EXTI0_1_IRQHandler();
	extern "C" void EXTI2_3_IRQHandler();
	extern "C" void EXTI4_15_IRQHandler();
	extern "C" void TSC_IRQHandler();
	extern "C" void DMA1_Channel1_IRQHandler();
	extern "C" void DMA1_Channel2_3_IRQHandler();
	extern "C" void DMA1_Channel4_5_IRQHandler();
	extern "C" void ADC1_IRQHandler();
	extern "C" void TIM1_BRK_UP_TRG_COM_IRQHandler();
	extern "C" void TIM1_CC_IRQHandler();
	extern "C" void TIM2_IRQHandler();
	extern "C" void TIM3_IRQHandler();
	extern "C" void TIM14_IRQHandler();
	extern "C" void TIM16_IRQHandler();
	extern "C" void TIM17_IRQHandler();
	extern "C" void SPI2_IRQHandler();
	extern "C" void SPI1_IRQHandler();
	extern "C" void USART1_IRQHandler();
	extern "C" void USART2_IRQHandler();
	extern "C" void I2C1_IRQHandler();
	extern "C" void CEC_CAN_IRQHandler();
	extern "C" void USB_IRQHandler();

	extern std::uint32_t _estack[];

	using isr_routine = void(*)();

	isr_routine interrupt_vector[]{
		reinterpret_cast<isr_routine>(_estack),
		Reset_Handler, // Reset Handler
		NMI_Handler, // NMI Handler
		HardFault_Handler, // Hard Fault Handler
		0, // Reserved
		0, // Reserved
		0, // Reserved
		0, // Reserved
		0, // Reserved
		0, // Reserved
		0, // Reserved
		SVC_Handler, // SVCall Handler
		0, // Reserved
		0, // Reserved
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
		0, // Reserved
		0, // Reserved
		TIM14_IRQHandler, // TIM14
		0, // Reserved
		TIM16_IRQHandler, // TIM16
		TIM17_IRQHandler, // TIM17
		I2C1_IRQHandler, // I2C1
		0, // Reserved
		SPI1_IRQHandler, // SPI1
		SPI2_IRQHandler, // SPI2
		USART1_IRQHandler, // USART1
		USART2_IRQHandler, // USART2
		0, // Reserved
		CEC_CAN_IRQHandler, // CECand CAN
		USB_IRQHandler, // USB
	};

	void Reset_Handler() {

	}


}