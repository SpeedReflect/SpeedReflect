#pragma once

#include <cstdint>
#include <iostream>
#include <filesystem>
#include "Memory.h"



namespace stdfs = std::filesystem;



namespace speedreflect
{
	enum class entry_points : std::uint32_t
	{
		underground1 = 0x00670CB5,
		underground2 = 0x0075BCC7,
		mostwanted = 0x007C4040,
		prostreet = 0x00828C25,
		carbon = 0x0087E926,
	};

	class game
	{
	public:
		virtual entry_points GameType() = 0;
		virtual void Process() = 0;
		virtual ~game() { }
	};

	struct vector_offset
	{
		std::uint32_t binkey;
		std::uint32_t offset;
		std::uint32_t size;
	};
}