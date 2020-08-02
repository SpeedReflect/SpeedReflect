#pragma once

#include <cstdint>
#include <iostream>
#include <filesystem>
#include "Memory.h"
#include "binary_reader.h"

namespace stdfs = std::filesystem;



namespace speedreflect
{
	const std::string empty = "";

	enum class entry_points : std::uint32_t
	{
		underground1 = 0x00670CB5,
		underground2 = 0x0075BCC7,
		mostwanted = 0x007C4040,
		prostreet = 0x00828C25,
		carbon = 0x0087E926,
	};

	enum class bin_block_id : std::uint32_t
	{
		cartypeinfo = 0x00034600,
		vinylsystem = 0x8003CE00,
	};

	struct vector_offset
	{
		std::uint32_t binkey;
		std::uint32_t offset;
		std::uint32_t size;
	};

	template <typename t> void set(std::uint32_t address, t value)
	{
		DWORD old;
		auto size = sizeof(value);
		VirtualProtect((LPVOID)address, size, PAGE_EXECUTE_READWRITE, &old);
		*reinterpret_cast<t*>(address) = value;
		VirtualProtect((LPVOID)address, size, old, &old);
	}

	template <typename t> void jump(std::uint32_t address, t function)
	{
		set<std::uint8_t>(address, 0xE9);
		set<std::uint32_t>(address + 1, std::uint32_t(function) - address - 5);
	}
}