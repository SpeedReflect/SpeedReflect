#pragma once

#include <cstdint>
#include <iostream>
#include <filesystem>
#include <unordered_map>
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
		preset_rides = 0x00030220,
		cartypeinfo = 0x00034600,
		gcareer_races = 0x00034A11,
		world_shops = 0x00034A12,
		gcareer_unused = 0x00034A13,
		gcareer_brands = 0x00034A14,
		part_performances = 0x00034A15,
		gshowcases = 0x00034A16,
		sms_messages = 0x00034A17,
		sponsors = 0x00034A19,
		gcareer_stages = 0x00034A18,
		perfslider_tunings = 0x00034A1A,
		world_challenges = 0x00034A1B,
		part_unlockables = 0x00034A1C,
		gcareer_strings = 0x00034A1D,
		bank_triggers = 0x00034A1E,
		gcar_unlocks = 0x00034A1F,
		vinylheader = 0x0003CE01,
		vinylhashheader = 0x0003CE0E,
		vinylcarentries = 0x0003CE0F,
		vinylfloatmatrix = 0x0003CE10,
		vinylvectorentry = 0x0003CE11,
		vinylmetadata = 0x0003CE13,
		gcareer = 0x80034A10,
		vinylsystem = 0x8003CE00,
		vinylhashtable = 0x8003CE0D,
	};

	struct vector_offset
	{
		std::uint32_t binkey;
		std::int32_t offset;
		std::int32_t size;
	};

	struct block
	{
		bin_block_id id;
		std::int32_t size;
		std::int32_t offset;
		std::int32_t lastpos;
		std::unordered_map<std::uint32_t, std::int32_t> key_to_offset;
		
		block(bin_block_id _id) : id(_id), size(0), offset(0), lastpos(0) { }

		std::int32_t get_offset_by_key(std::uint32_t key)
		{
			auto result = this->key_to_offset.find(key);
			if (result == this->key_to_offset.end()) return -1;
			else return result->second;
		}
		void print()
		{
			std::printf("ID: [0x%08X] | Size: [0x%08X] | Offset: [0x%08X]\n", static_cast<std::int32_t>(this->id), this->size, this->offset);
		}
	};

	namespace utils
	{
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

		std::uint32_t bin_hash(const char* hash);
	}
}