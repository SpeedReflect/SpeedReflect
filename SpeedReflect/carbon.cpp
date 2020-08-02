#include "pch.h"
#include "carbon.h"



namespace speedreflect::carbon
{
    BOOL(__cdecl* HandleCarStreamingSolidHeader)(char* a2, int a3, int a4, short a5) = (BOOL (__cdecl*)(char*, int, int, short))0x0055F670;

    struct headers
    {
        const char* wheels = "CARS\\WHEELS\\GEOMETRY.BIN";
        const char* wheels2 = "CARS\\WHEELS2\\GEOMETRY.BIN";
        const char* wheels3 = "CARS\\WHEELS3\\GEOMETRY.BIN";
        const char* wheels4 = "CARS\\WHEELS4\\GEOMETRY.BIN";
        const char* wheels5 = "CARS\\WHEELS5\\GEOMETRY.BIN";
        const char* wheels6 = "CARS\\WHEELS6\\GEOMETRY.BIN";
        const char* spoiler = "CARS\\SPOILER\\GEOMETRY.BIN";
        const char* spoiler_as2 = "CARS\\SPOILER_AS2\\GEOMETRY.BIN";
        const char* spoiler_carerra = "CARS\\SPOILER_CARRERA\\GEOMETRY.BIN";
        const char* spoiler_carerra_as2 = "CARS\\SPOILER_CARRERA_AS2\\GEOMETRY.BIN";
        const char* spoiler_hatch = "CARS\\SPOILER_HATCH\\GEOMETRY.BIN";
        const char* spoiler_hatch_as2 = "CARS\\SPOILER_HATCH_AS2\\GEOMETRY.BIN";
        const char* spoiler_porsches = "CARS\\SPOILER_PORSCHES\\GEOMETRY.BIN";
        const char* spoiler_porsches_as2 = "CARS\\SPOILER_PORSCHES_AS2\\GEOMETRY.BIN";
        const char* spoiler_custom = "CARS\\SPOILER_CUSTOM\\GEOMETRY.BIN";
        const char* spoiler_custom_as2 = "CARS\\SPOILER_CUSTOM_AS2\\GEOMETRY.BIN";
        const char* roof_scoop = "CARS\\ROOF_SCOOP\\GEOMETRY.BIN";
        const char* exhaust = "CARS\\EXHAUST\\GEOMETRY.BIN";
    } ptr;

    void make_geo_writeout()
    {
        HandleCarStreamingSolidHeader((char*)ptr.wheels, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.wheels2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.wheels3, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.wheels4, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.wheels5, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.wheels6, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.spoiler, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.spoiler_as2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.spoiler_carerra, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.spoiler_carerra_as2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.spoiler_hatch, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.spoiler_hatch_as2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.spoiler_porsches, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.spoiler_porsches_as2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.spoiler_custom, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.spoiler_custom_as2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.roof_scoop, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)ptr.exhaust, 0, 0, 0);
    }

    __declspec(naked) void detour_ano()
    {
        __asm
        {

            test edi, edi;
            jnz quit;

            call make_geo_writeout;

        quit:
            push 0x007B14DD;
            retn;

        }
    }

    __declspec(naked) void detour_geo()
    {
        __asm
        {

            call make_geo_writeout;
            push 0x007B14DD;
            retn;

        }
    }

    bool make_vectable(const stdfs::path& file, vector_offset** vArray, std::uint32_t* vArrayLen)
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

    void make_geotable()
    {
        speedreflect::jump(0x007B1880, detour_geo);
        speedreflect::jump(0x007B14BB, detour_ano);
    }

    void process()
    {
        const auto& directory = stdfs::current_path().parent_path();
        const auto& vinyls_path = directory / "CARS" / "VINYLS" / "VINYLS.BIN";
        const auto& logos_path = directory / "FRONTEND" / "LOGOS.BIN";
        const auto& globalb_path = directory / "GLOBAL" / "GLOBALB.LZC";

        Memory::Init();

        make_vectable(vinyls_path, reinterpret_cast<vector_offset**>(0x00A7AAD4), reinterpret_cast<std::uint32_t*>(0xA7AAD8));
        make_vectable(logos_path, reinterpret_cast<vector_offset**>(0x00A71250), reinterpret_cast<std::uint32_t*>(0xA71254));

        const unsigned int val = *reinterpret_cast<std::uint32_t*>(0x00A7AAD4);

        Memory::writeRaw(0x007CE5DE + 1, true, 4, (val & 0xFF), (val >> 8) & 0xFF, (val >> 16) & 0xFF, (val >> 24) & 0xFF);
        make_geotable();
    }
}
