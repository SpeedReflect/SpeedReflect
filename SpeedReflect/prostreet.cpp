#include "pch.h"
#include "prostreet.h"



namespace speedreflect::prostreet
{
    auto HandleCarStreamingSolidHeader = (BOOL(__cdecl*)(char*, int, int, short))0x00458070;
    auto eLoadStreamingTexturePack = (BOOL(__cdecl*)(char*, void(__cdecl*)(void*), int, short))0x00459AF0;

    std::vector<std::string> streaming_geo_headers;
    std::vector<std::string> streaming_tex_headers;

    struct geometry_headers
    {
        const char* group01 = "CARS\\GROUP01\\GEOMETRY.BIN";
        const char* group02 = "CARS\\GROUP02\\GEOMETRY.BIN";
        const char* group03 = "CARS\\GROUP03\\GEOMETRY.BIN";
        const char* group04 = "CARS\\GROUP04\\GEOMETRY.BIN";
        const char* group05 = "CARS\\GROUP05\\GEOMETRY.BIN";
        const char* group06 = "CARS\\GROUP06\\GEOMETRY.BIN";
        const char* group07 = "CARS\\GROUP07\\GEOMETRY.BIN";
        const char* group08 = "CARS\\GROUP08\\GEOMETRY.BIN";
        const char* brake = "CARS\\BRAKE\\GEOMETRY.BIN";
        const char* brakerotor = "CARS\\BRAKEROTOR\\GEOMETRY.BIN";
        const char* spoiler = "CARS\\SPOILER\\GEOMETRY.BIN";
        const char* roofscoop = "CARS\\ROOFSCOOP\\GEOMETRY.BIN";
        const char* exhaust = "CARS\\EXHAUST\\GEOMETRY.BIN";
        const char* seat = "CARS\\SEAT\\GEOMETRY.BIN";
    } geometry_table;

    struct texture_headers
    {
        const char* textures = "CARS\\TEXTURES.BIN";
        const char* spoiler = "CARS\\SPOILER\\TEXTURES.BIN";
        const char* exhaust = "CARS\\EXHAUST\\TEXTURES.BIN";
        const char* seat = "CARS\\SEAT\\TEXTURES.BIN";
        const char* group01 = "CARS\\GROUP01\\TEXTURES.BIN";
        const char* group02 = "CARS\\GROUP02\\TEXTURES.BIN";
        const char* group03 = "CARS\\GROUP03\\TEXTURES.BIN";
        const char* group04 = "CARS\\GROUP04\\TEXTURES.BIN";
        const char* group05 = "CARS\\GROUP05\\TEXTURES.BIN";
        const char* group06 = "CARS\\GROUP06\\TEXTURES.BIN";
        const char* group07 = "CARS\\GROUP07\\TEXTURES.BIN";
        const char* group08 = "CARS\\GROUP08\\TEXTURES.BIN";
        const char* brake = "CARS\\BRAKE\\TEXTURES.BIN";
        const char* brakerotor = "CARS\\BRAKEROTOR\\TEXTURES.BIN";
        const char* vinyls = "CARS\\VINYLS\\LIVERYTEXTURES.BIN";
    } texture_table;

    void make_geo_writeout()
    {
        std::printf("Function [make_geo_writeout] has been called...\n");

        HandleCarStreamingSolidHeader((char*)geometry_table.group01, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.group02, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.group03, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.group04, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.group05, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.group06, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.group07, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.group08, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.brake, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.brakerotor, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.roofscoop, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.exhaust, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.seat, 0, 0, 0);

        for (const auto& header : streaming_geo_headers)
        {

            const auto& bin = "CARS\\" + header + "\\GEOMETRY.BIN";
            auto ptr = (char*)bin.c_str();

            std::printf("Loading file [%s]...\n", bin.c_str());
            HandleCarStreamingSolidHeader(ptr, 0, 0, 0);
            std::printf("Finished loading file [%s]\n", bin.c_str());

        }

        std::printf("Function [make_geo_writeout] ended execution...\n");
    }

    void make_tex_writeout()
    {
        std::printf("Function [make_tex_writeout] has been called...\n");

        eLoadStreamingTexturePack((char*)texture_table.textures, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.spoiler, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.exhaust, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.seat, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.group01, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.group02, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.group03, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.group04, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.group05, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.group06, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.group07, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.group08, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.brake, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.brakerotor, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.vinyls, 0, 0, 0);

        for (const auto& header : streaming_tex_headers)
        {

            const auto& bin = "CARS\\" + header + "\\TEXTURES.BIN";
            auto ptr = (char*)bin.c_str();

            std::printf("Loading file [%s]...\n", bin.c_str());
            eLoadStreamingTexturePack(ptr, 0, 0, 0);
            std::printf("Finished loading file [%s]\n", bin.c_str());

        }

        std::printf("Function [make_tex_writeout] ended execution...\n");
    }

    __declspec(naked) void detour_stream_geo()
    {
        __asm
        {

            pushad;
            call make_geo_writeout;
            popad;
            push 0x00755DCC;
            retn;

        }
    }

    __declspec(naked) void detour_stream_tex()
    {
        __asm
        {

            pushad;
            call make_tex_writeout;
            popad;
            push 0x00755C02;
            retn;

        }
    }

    void load_streaming_headers(const stdfs::path& file)
    {
        const auto filename = file.wstring();
        auto br = binary_reader(filename);
        if (!br) return;

        while (br.position() < br.length())
        {

            const auto offset = br.position();
            const auto id = static_cast<bin_block_id>(br.read_uint32());
            const auto size = br.read_int32();

            if (id == bin_block_id::cartypeinfo)
            {

                br.advance(8);
                auto count = size / 0xD0;

                for (std::int32_t i = 0; i < count; ++i)
                {

                    auto cname = br.read_string(0x10);
                    br.advance(0x40);
                    auto key = br.read_uint32();
                    br.advance(0x40);
                    auto usage = br.read_int32();
                    br.advance(0x38);

                    if (usage == 3)
                    {

                        streaming_tex_headers.push_back(cname);
                        streaming_geo_headers.push_back(cname);

                    }
                    else if (usage == 4)
                    {

                        streaming_geo_headers.push_back(cname);

                    }

                }

            }

            br.position(offset + size + 8);

        }

        utils::jump(0x00755DB0, detour_stream_geo);
        utils::jump(0x00755BE1, detour_stream_tex);
    }

    void make_vectors(const stdfs::path& file, std::uint32_t addr_table, std::uint32_t addr_count)
    {
        auto br = binary_reader(file.wstring());
        if (!br) return;

        std::vector<vector_offset> vec_entries;

        while (br.position() < br.length())
        {

            auto cur = br.position();
            auto id = static_cast<bin_block_id>(br.read_uint32());
            auto size = br.read_int32();

            if (id == bin_block_id::vinylsystem)
            {

                while (br.position() < cur + size + 8)
                {

                    auto subid = static_cast<bin_block_id>(br.read_uint32());
                    auto subsize = br.read_int32();

                    if (subid == bin_block_id::vinylheader)
                    {

                        br.advance(0x10);
                        auto key = br.read_uint32();
                        vec_entries.push_back(vector_offset{ key, cur, (size + 8) });
                        break;

                    }

                }

            }

            br.position(cur + size + 8);

        }

        auto total = vec_entries.size();
        auto table = reinterpret_cast<vector_offset*>(calloc(total, sizeof(vector_offset)));
        auto ptr = reinterpret_cast<std::uint32_t>(table);

        for (size_t i = 0; i < total; ++i)
        {

            std::memcpy(&table[i], &vec_entries[i], sizeof(vector_offset));

        }

        utils::set(addr_table, table);
        utils::set(addr_count, total);
        std::printf("Writing vector table pointer [0x%08X] to address [0x%08X]\n", ptr, addr_table);
        std::printf("Writing vector table count [%d] to address [0x%08X]\n", total, addr_count);
    }

	void process()
	{
        const auto& directory = stdfs::current_path().parent_path();
        const auto& vinyls_path = directory / "CARS" / "VINYLS" / "VINYLS.BIN";
        const auto& globalb_path = directory / "GLOBAL" / "GLOBALB.LZC";

        make_vectors(vinyls_path, 0x00A84924, 0x00A84928);
        load_streaming_headers(globalb_path);
	}
}
