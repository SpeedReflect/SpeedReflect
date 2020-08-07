#include "pch.h"
#include "carbon.h"



namespace speedreflect::carbon
{
    auto HandleCarStreamingSolidHeader = (BOOL (__cdecl*)(char*, int, int, short))0x0055F670;
    auto eLoadStreamingTexturePack = (BOOL(__cdecl*)(char*, void(__cdecl*)(void*), int, short))0x0055F850;

    std::vector<std::string> streaming_geo_headers;
    std::vector<std::string> streaming_tex_headers;

    struct geometry_headers
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
    } geometry_table;
    
    struct texture_headers
    {
        const char* textures = "CARS\\TEXTURES.BIN";
        const char* spoiler = "CARS\\SPOILER\\TEXTURES.BIN";
        const char* exhaust = "CARS\\EXHAUST\\TEXTURES.BIN";
        const char* wheels = "CARS\\WHEELS\\TEXTURES.BIN";
        const char* wheels2 = "CARS\\WHEELS2\\TEXTURES.BIN";
        const char* wheels3 = "CARS\\WHEELS3\\TEXTURES.BIN";
        const char* wheels4 = "CARS\\WHEELS4\\TEXTURES.BIN";
        const char* wheels5 = "CARS\\WHEELS5\\TEXTURES.BIN";
        const char* wheels6 = "CARS\\WHEELS6\\TEXTURES.BIN";
        const char* precompvinyls = "CARS\\PRECOMPVINYLS\\PRECOMPVINYLS.BIN";
        const char* precompvinylslowrez = "CARS\\PRECOMPVINYLS\\PRECOMPVINYLSLOWREZ.BIN";
    } texture_table;

    struct generic_headers
    {
        const char* brakes_geo = "CARS\\BRAKES\\GEOMETRY.BIN";
        const char* brakes_tex = "CARS\\BRAKES\\TEXTURES.BIN";
        const char* plates_geo = "CARS\\PLATES\\GEOMETRY.BIN";
        const char* plates_tex = "CARS\\PLATES\\TEXTURES.BIN";
    } generic_table;

    void make_geo_writeout()
    {
        std::printf("Function [make_geo_writeout] has been called...\n");

        HandleCarStreamingSolidHeader((char*)geometry_table.wheels, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.wheels2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.wheels3, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.wheels4, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.wheels5, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.wheels6, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler_as2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler_carerra, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler_carerra_as2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler_hatch, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler_hatch_as2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler_porsches, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler_porsches_as2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler_custom, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.spoiler_custom_as2, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.roof_scoop, 0, 0, 0);
        HandleCarStreamingSolidHeader((char*)geometry_table.exhaust, 0, 0, 0);

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
        eLoadStreamingTexturePack((char*)texture_table.wheels, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.wheels2, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.wheels3, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.wheels4, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.wheels5, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.wheels6, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.precompvinyls, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.precompvinylslowrez, 0, 0, 0);

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

    __declspec(naked) void detour_stream_geo1()
    {
        __asm
        {

            call make_geo_writeout;
            push 0x007B14DD;
            retn;

        }
    }

    __declspec(naked) void detour_stream_geo2()
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

    __declspec(naked) void detour_stream_tex()
    {
        __asm
        {

            call make_tex_writeout;
            push 0x007B1522;
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

        utils::jump(0x007B1880, detour_stream_geo1);
        utils::jump(0x007B14BB, detour_stream_geo2);
        utils::jump(0x007B1501, detour_stream_tex);
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
        const auto& logos_path = directory / "FRONTEND" / "LOGOS.BIN";
        const auto& globalb_path = directory / "GLOBAL" / "GLOBALB.LZC";

        make_vectors(vinyls_path, 0x00A7AAD4, 0x00A7AAD8);
        make_vectors(logos_path, 0x00A71250, 0x00A71254);

        auto address = *reinterpret_cast<std::uint32_t*>(0x00A7AAD4);
        utils::set(0x007CE5DF, address);

        load_streaming_headers(globalb_path);
    }
}
