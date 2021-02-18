#include "adc.hpp"

#include <ufsel/bit_operations.hpp>
#include <ufsel/itertools.hpp>

#include <climits>
#include <cstdio>
#include <array>

namespace bsp::adc {

    static volatile uint16_t readings[regularConversionLength];

    void Init(void) {
        using namespace ufsel;
        //enable clocks to DMA1 and ADC1
        bit::set(std::ref(RCC->APB2ENR), RCC_APB2ENR_ADCEN);
        bit::set(std::ref(RCC->AHBENR), RCC_AHBENR_DMAEN);

        bit::set(std::ref(ADC1->CFGR1),
            //leave default 12bit resolution and right alignment
            ADC_CFGR1_DMACFG, //enable DMA circular mode
            ADC_CFGR1_DMAEN, //enable DMA access mode
            ADC_CFGR1_CONT //enable continuous mode
            );

        //clock ADC from APB/4
        bit::sliceable_reference{ADC1->CFGR2}[31_to, 30] = 0b10; 

        constexpr std::array conversion_sequence = {
            //zero based indices of channels measured during regular conversion sequence
            17
        };
        static_assert(regularConversionLength == std::size(conversion_sequence), "Length of regular ADC conversion sequence does not match the number of channels.");
        static_assert(regularConversionLength <= 16, "There may be at most 16 conversions in a regular group...");

        //TODO consider adjusting this to the needs of application (correct sampling frequency for each signal)
        constexpr int sample_time = 0b111; //sample time of 239.5 clock cycles
        ADC1->SMPR = sample_time;

        for (auto channel : conversion_sequence) //select channels used for conversion
            bit::set(std::ref(ADC1->CHSELR), bit::bit(channel));

        bit::set(std::ref(ADC1_COMMON->CCR),
            ADC_CCR_TSEN, //enable temperature sensor
            ADC_CCR_VREFEN //enable internal reference
            );

        //ADC1 generates requests for DMA1 channel 1
        DMA_Channel_TypeDef & dma = *DMA1_Channel1;
        bit::set(std::ref(dma.CCR),
            0b01 << DMA_CCR_PL_Pos, //medium channel priority
            0b01 << DMA_CCR_MSIZE_Pos, //16bits memory size
            0b10 << DMA_CCR_PSIZE_Pos, //32bit peripheral size
            DMA_CCR_MINC, //memory increment mode
            DMA_CCR_CIRC, //circular mode
            DMA_CCR_TCIE //enable transfer complete interrupt
            );

        dma.CNDTR = regularConversionLength;
        dma.CPAR = reinterpret_cast<std::uint32_t>(&ADC1->DR);
        dma.CMAR = reinterpret_cast<std::uint32_t>(&readings[0]);

        NVIC_EnableIRQ(DMA1_Channel1_IRQn);

        //enable the AD converter
        bit::set(std::ref(ADC1->CR), ADC_CR_ADEN);

        bit::set(std::ref(ADC1->CR), ADC_CR_ADCAL); //Start ADC calibration
        bit::wait_until_cleared(ADC1->CR, ADC_CR_ADCAL); //Wait for it to end

        //enable DMA1 channel 1
        bit::set(std::ref(dma.CCR), DMA_CCR_EN);

        //start ADC conversion
        bit::set(std::ref(ADC1->CR), ADC_CR_ADSTART);
    }

    uint16_t ReadoutRaw(Channel ch) {
        int const index = static_cast<int>(ch);
        //TODO add assert(reading[index] < ConversionRange);
        return readings[index];
    }

    Temperature getAmbientTemperature() {
        return 0_degC; //TODO implement
    }
}

extern "C" void DMA1_Channel1_IRQHandler(void) {
    // TODO: consider double-buffering the results
    DMA1->IFCR = DMA_IFCR_CTCIF1;

    //TODO call some function to detect brownout
}

