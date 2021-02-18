#pragma once

#include <Drivers/stm32f042x6.h>

#include <cstdint>
#include <ufsel/bit_operations.hpp>

struct Pin {
	enum class Mode : std::uint8_t {
		input = 0,
		outPP = 1,
		outOD = 1 + 16,
		alternatePP = 2,
		alternateOD = 2 + 16,
		analog = 3
	};

	enum class Pull {
		none = 0, up = 1, down = 2
	};

	enum class Speed {
		slow = 0, medium = 1, fast = 3
	};

	constexpr Pin(std::uintptr_t gpio, uint16_t mask, Mode mode, Speed speed, Pull pull, unsigned char alternate = 0)
		: address(gpio), pin(mask), mode_{mode}, pull_{pull}, speed_{speed}, alternate_{alternate} {}

	GPIO_TypeDef* gpio() const {
		return reinterpret_cast<GPIO_TypeDef*>(address);
	}

	void Set() const { //TODO make not const as soon as constinit replaces constexpr in file gpio.hpp
		gpio()->BSRR = pin;
	}

	void Clear() const {
		gpio()->BRR = pin;
	}

	void Toggle() const { //TODO these shall not be const member methods. 
		ufsel::bit::toggle(std::ref(gpio()->ODR), pin);
	}

	uint16_t Read() const {
		return ufsel::bit::get(gpio()->IDR, pin);
	}

	void Write(uint32_t value) const {
		if (value)
			Set();
		else
			Clear();
	}

	std::uintptr_t const address;
	uint16_t const pin;
	Mode const mode_;
	Pull const pull_;
	Speed const speed_;
	unsigned char const alternate_;
};

template <unsigned int bits, typename ShiftReg_t = uint32_t>
class FilteredPin {
public:
	ShiftReg_t const mask = (1 << bits) - 1;

	FilteredPin(Pin const& pin) : pin(pin), shiftReg(0) {}

	bool IsAllSet() const volatile { return shiftReg == mask; }
	bool IsAllCleared() const volatile { return shiftReg == 0; }

	bool IsAnySet() const volatile { return shiftReg != 0; }
	bool IsAnyCleared() const volatile { return shiftReg != mask; }

	void Sample() volatile {
		shiftReg = ((shiftReg << 1) | (pin.Read() ? 1 : 0)) & mask;
	}

	ShiftReg_t GetShiftReg() const volatile {
		return shiftReg;
	}

private:
	Pin const& pin;
	ShiftReg_t shiftReg;
};
