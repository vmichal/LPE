/*
 * eForce Accumulator Management System
 *
 * Written by Vojtech Michal
 *
 * Copyright (c) 2021 eforce FEE Prague Formula
 */

#pragma once


#include <ufsel/bit_operations.hpp>

#include <cstddef>
#include <cstdint>
#include <span>

#include <Drivers/stm32f042x6.h>

namespace bsp::flash {

	enum class WriteStatus {
		Ok,
		AlreadyWritten
	};

	inline void lock() { ufsel::bit::set(std::ref(FLASH->CR), FLASH_CR_LOCK); }
	inline void unlock() {
		FLASH->KEYR = 0x45670123;
		FLASH->KEYR = 0xcdef89ab;
	}

	void ErasePage(std::uint32_t pageAddress);
	WriteStatus Write(std::uint32_t flashAddress, std::uint32_t word);
	WriteStatus Write(std::uint32_t flashAddress, std::uint16_t halfWord);
	WriteStatus Write(std::uint32_t flashAddress, std::span<std::uint8_t> data);
	
	//Constructing an object of this type enables write access to the flash memory until the end of its lifetime
	struct RAII_unlocker {
		RAII_unlocker() { unlock(); }
		~RAII_unlocker() { lock(); }
	};

}
