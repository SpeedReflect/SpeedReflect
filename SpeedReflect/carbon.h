#pragma once

#include "types.h"

namespace speedreflect
{

	class carbon : game
	{
	private:
		stdfs::path directory_;
		stdfs::path vinyls_path_;
		stdfs::path logos_path_;
		stdfs::path globalb_path_;

	public:
		~carbon() { }
		entry_points GameType() override;
		void Process() override;

	private:
		void InitPaths();
		bool make_vectable(const stdfs::path& file, vector_offset** vArray, std::uint32_t* vArrayLen);

	};

}
