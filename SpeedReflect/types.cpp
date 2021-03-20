#include "pch.h"
#include "types.h"



namespace speedreflect::utils
{
	std::uint32_t bin_hash(const char* hash)
	{
		std::uint32_t result = 0xFFFFFFFF;

		while (*hash != NULL)
		{

			result *= 0x21;
			result += *hash++;

		}

		return result;
	}

	bool is_compressed(binary_reader* br)
	{
		auto comp = br->read_uint32();
		br->advance(-4);

		switch (comp)
		{

		case 'ZLDJ':
		case 'FFUH':
		case 'WWAR':
		case 'PMOC':
		case 'KPFR':
			return true;

		default:
			return false;

		}
	}
}