

#include "timer.hpp"
#include "assert.hpp"
#include <cstdint>
#include <array>
#include <bit>

void BlockingDelay(Duration const time) {
    Timestamp const start = Timestamp::Now();
    for (;Timestamp::Now() - start < time;);
}


void MicrosecondTimer::Initialize()
{
    using namespace ufsel;

    //enable clock to peripherals
    bit::set(std::ref(RCC->APB1ENR), RCC_APB1ENR_TIM14EN);
    bit::set(std::ref(RCC->APB2ENR), RCC_APB2ENR_TIM16EN, RCC_APB2ENR_TIM17EN);

    for (auto& timer : timers) {
        ufsel::bit::set(std::ref(timer.CR1), TIM_CR1_URS); //Let both timers assert the update flag only on counter overflow
        timer.CNT = 0;
        timer.PSC = bsp::clock::SYSCLK / 1_MHz - 1; //make the timer count microseconds
        timer.ARR = 0xff'ff;
    }

}

