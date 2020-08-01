#include "pch.h"
#include "carbon.h"



namespace speedreflect
{
	entry_points carbon::GameType()
	{
		return entry_points::carbon;
	}

	void carbon::Process()
	{
        this->InitPaths();
        this->make_vectable(this->vinyls_path_, reinterpret_cast<vector_offset**>(0xA7AAD4), reinterpret_cast<std::uint32_t*>(0xA7AAD8));
        this->make_vectable(this->logos_path_, reinterpret_cast<vector_offset**>(0xA71250), reinterpret_cast<std::uint32_t*>(0xA71254));

        const unsigned int val = *reinterpret_cast<std::uint32_t*>(0xA7AAD4);

        Memory::Init();
        Memory::writeRaw(0x7CE5DE + 1, true, 4, (val & 0xFF), (val >> 8) & 0xFF, (val >> 16) & 0xFF, (val >> 24) & 0xFF);
	}

    void carbon::InitPaths()
    {
        this->directory_ = stdfs::current_path().parent_path();
        this->vinyls_path_ = this->directory_ / "CARS" / "VINYLS" / "VINYLS.BIN";
        this->logos_path_ = this->directory_ / "FRONTEND" / "LOGOS.BIN";
        this->globalb_path_ = this->directory_ / "GLOBAL" / "GLOBALB.LZC";
    }

    bool carbon::make_vectable(const stdfs::path& file, vector_offset** vArray, std::uint32_t* vArrayLen)
    {
        if (!stdfs::exists(file)) return false;

        FILE* vinyls_file;
        const auto filename = file.wstring();
        if (_wfopen_s(&vinyls_file, filename.c_str(), L"rb") || !vinyls_file) return false;

        struct _stat32 stat32;
        if (_wstat32(filename.c_str(), &stat32)) return false;

        std::vector<vector_offset> offset_entries;

        while (ftell(vinyls_file) < stat32.st_size)
        {

            const auto offset = static_cast<std::uint32_t>(ftell(vinyls_file));
            std::uint32_t chunk_id;
            std::uint32_t chunk_size;
            fread_s(&chunk_id, 4, 4, 1, vinyls_file);
            fread_s(&chunk_size, 4, 4, 1, vinyls_file);
            auto* const chunk_data = static_cast<std::uint8_t*>(calloc(chunk_size, 1));

            if (!chunk_data) return false;

            fread_s(chunk_data, chunk_size, 1, chunk_size, vinyls_file);

            if (chunk_id == 0x8003CE00)
            {

                const unsigned int vinyl_key = *reinterpret_cast<std::uint32_t*>(chunk_data + 0x18);
                const auto full_chunk_size = chunk_size + 8;

                offset_entries.push_back(vector_offset{ vinyl_key, offset, full_chunk_size });

            }

        }

        auto new_mem = (vector_offset*)calloc(offset_entries.size(), sizeof(vector_offset));

        for (size_t i = 0; i < offset_entries.size(); i++)
        {

            memcpy(&new_mem[i], &offset_entries[i], sizeof(vector_offset));

        }

        *vArray = new_mem;
        *vArrayLen = offset_entries.size();
        return true;
    }
}