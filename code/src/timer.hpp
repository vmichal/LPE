

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H

#include <Drivers/stm32f042x6.h>

#include <ufsel/units.hpp>
#include <ufsel/bit_operations.hpp>
#include <optional>
#include <utility>
#include <array>
#include <cstdint>

#include <ufsel/units.hpp>
#include "assert.hpp"
#include "core.hpp"

#include <cstdint>

extern std::uint32_t volatile SystemTicks;
void BlockingDelay(Duration time);

struct Timestamp {

	constexpr Timestamp(uint32_t tick) : tick(tick) {}

	bool TimeElapsed(Duration const duration) const {
		return Timestamp::Now() - *this > duration;
	}

	static Timestamp Now() {
		return Timestamp{ SystemTicks };
	}

	constexpr Duration operator-(Timestamp other) const {
		return Duration{ tick - other.tick };
	}

	friend constexpr bool operator< (Timestamp a, Timestamp b) { return a.tick < b.tick; }
	friend constexpr bool operator> (Timestamp a, Timestamp b) { return a.tick > b.tick; }
	friend constexpr bool operator<=(Timestamp a, Timestamp b) { return a.tick <= b.tick; }
	friend constexpr bool operator>=(Timestamp a, Timestamp b) { return a.tick >= b.tick; }
	friend constexpr bool operator==(Timestamp a, Timestamp b) { return a.tick == b.tick; }
	friend constexpr bool operator!=(Timestamp a, Timestamp b) { return a.tick != b.tick; }
private:
	uint32_t tick;
};


class SysTickTimer {
public:

	SysTickTimer() : startTime{ Timestamp::Now() } {}

	void Restart() {
		startTime = Timestamp::Now();
	}

	Duration GetTimeElapsed() const {
		return Timestamp::Now() - startTime;
	}

	bool TimeElapsed(Duration const interval) const {
		return startTime.TimeElapsed(interval);
	}

	bool RestartIfTimeElapsed(Duration const interval) {
		if (TimeElapsed(interval)) {
			this->Restart();
			return true;
		}
		else {
			return false;
		}
	}

private:
	Timestamp startTime;
};


constexpr auto SYS_CLK = bsp::clock::SYSCLK; 

constexpr auto TIM17_frequency = 1'000'000_Hz;
constexpr auto TIM16_frequency = 1'000'000_Hz;
constexpr auto TIM14_frequency = 1'000'000_Hz;

enum class MeasurementState {
	ready,
	waiting_for_first_irq,
	waiting_for_second_irq
};

//Wraps basic timers TIM6, TIM7 with megahertz frequency
struct MicrosecondTimer {
	static_assert(TIM14_frequency == TIM17_frequency && TIM16_frequency == TIM17_frequency && TIM17_frequency == 1'000'000_Hz, "You better fulfil this to get microsecond resolution.");

	//TIM6 will be used for task timing, TIM7 for timing of the whole main loop
	static inline std::array timers {*TIM14, *TIM16, *TIM17};

private:
	TIM_TypeDef& timer_;

public:
	MicrosecondTimer(TIM_TypeDef & timer) : timer_{timer} {
		assert(ufsel::bit::all_cleared(timer.CR1, TIM_CR1_CEN)); //This timer is used by someone, otherwise it would be disabled in dtor
		assert(timer.CNT == 0 && ufsel::bit::all_cleared(timer.SR, TIM_SR_UIF)); //It should have been reset in the destructor as well

		ufsel::bit::set(std::ref(timer.CR1), TIM_CR1_CEN); //Start the counter
	}

	~MicrosecondTimer() { //Reset the underlying timer for further use
		using namespace ufsel;
		assert(bit::all_set(timer_.CR1, TIM_CR1_CEN)); //This timer must have been activated by the constructor
		bit::clear(std::ref(timer_.CR1), TIM_CR1_CEN); //Disable the timer
		timer_.CNT = 0; //Clear the count register
		bit::set(std::ref(timer_.EGR), TIM_EGR_UG); //Update the timer
		bit::clear(std::ref(timer_.SR), TIM_SR_UIF); //Clean update interrupt flag
	}

	std::uint32_t get() const {
		bool const overflowed = ufsel::bit::get(timer_.SR, TIM_SR_UIF);
		return overflowed ? std::numeric_limits<std::uint16_t>::max() : timer_.CNT;
	}

	static void Initialize();

};

#endif /*__TIMER_H */

/* END OF FILE */
