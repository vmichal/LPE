#include "flash.hpp"
#include "assert.hpp"

namespace bsp::flash {
	using namespace ufsel;

	void ErasePage(std::uint32_t pageAddress) {

		bit::set(std::ref(FLASH->SR), FLASH_SR_EOP, FLASH_SR_WRPRTERR, FLASH_SR_PGERR);

		bit::wait_until_cleared(FLASH->SR, FLASH_SR_BSY); //wait for previous operation to end

		bit::set(std::ref(FLASH->CR), FLASH_CR_PER);
		FLASH->AR = pageAddress;
		bit::set(std::ref(FLASH->CR), FLASH_CR_STRT);
	}

	WriteStatus Write(std::uint32_t address, std::uint16_t halfWord) {
		auto const cachedResult = FLASH->SR;
		bit::set(std::ref(FLASH->SR), FLASH_SR_EOP, FLASH_SR_PGERR);

		bit::wait_until_cleared(FLASH->SR, FLASH_SR_BSY); //wait for previous operation to end
		bit::set(std::ref(FLASH->CR), FLASH_CR_PG); //enable flash programming
		bit::access_register<std::uint16_t>(address) = halfWord; //initiate programming

		assert(bit::all_cleared(cachedResult, FLASH_SR_WRPRTERR));

		return bit::all_set(cachedResult, FLASH_SR_PGERR) ? WriteStatus::AlreadyWritten : WriteStatus::Ok;
	}

	WriteStatus Write(std::uint32_t address, std::uint32_t word) {
		auto const cachedResult = FLASH->SR;
		bit::set(std::ref(FLASH->SR), FLASH_SR_EOP, FLASH_SR_PGERR);

		bit::wait_until_cleared(FLASH->SR, FLASH_SR_BSY); //wait for previous operation to end
		bit::set(std::ref(FLASH->CR), FLASH_CR_PG); //enable flash programming
		bit::access_register<std::uint16_t>(address) = word; //program lower half

		bit::wait_until_cleared(FLASH->SR, FLASH_SR_BSY); //wait for first operation to end
		bit::access_register<std::uint16_t>(address + 2) = word >> 16; //program upper half

		assert(bit::all_cleared(cachedResult, FLASH_SR_WRPRTERR));

		return bit::all_set(cachedResult, FLASH_SR_PGERR) ? WriteStatus::AlreadyWritten : WriteStatus::Ok;
	}

	WriteStatus Write(std::uint32_t flashAddress, std::span<std::uint8_t> const data) {

		for (std::size_t i = 0; i < data.size() / 2; ++i, flashAddress += 2) {
			std::uint16_t const half = data[2*i] | data[2*i + 1] << 16;
			if (auto const res = Write(flashAddress, half); res != WriteStatus::Ok)
				return res;
		}

		if (data.size() % 2 == 1) { //one byte extra
			std::uint16_t const half = data.back() | 0xff'ff << 16;
			if (auto const res = Write(flashAddress, half); res != WriteStatus::Ok)
				return res;
		}
		return WriteStatus::Ok;
	}

}
