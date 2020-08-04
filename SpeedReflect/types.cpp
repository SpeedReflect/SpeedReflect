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
}