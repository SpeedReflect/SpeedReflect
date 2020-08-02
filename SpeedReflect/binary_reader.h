#pragma once

#include "types.h"

namespace speedreflect
{

	class binary_reader
	{
	private:
		std::wstring filename_;
		std::int32_t position_;
		std::int32_t length_;
		FILE* handle_;
		bool is_ready_;

	public:
		~binary_reader();
		binary_reader(std::wstring& path);
		void read(void* dest, size_t size);
		template <typename t> void read(t* object);
		bool read_boolean();
		std::int8_t read_char();
		std::uint8_t read_byte();
		std::int16_t read_int16();
		std::uint16_t read_uint16();
		std::int32_t read_int32();
		std::uint32_t read_uint32();
		std::int64_t read_int64();
		std::uint64_t read_uint64();
		float read_single();
		double read_double();
		std::string read_string();
		std::string read_string(std::int32_t maxlen);
		std::int32_t position();
		void position(std::int32_t at);
		std::int32_t length();
		std::wstring path();
		operator bool() const;

	private:
		void check_space(size_t size);
		binary_reader(const binary_reader&) = delete;
		binary_reader& operator=(const binary_reader&) = delete;
	};

}
