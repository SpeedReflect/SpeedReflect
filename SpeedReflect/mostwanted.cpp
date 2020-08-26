#include "pch.h"
#include "mostwanted.h"



namespace speedreflect::mostwanted
{
	auto eLoadStreamingTexturePack = (BOOL(__cdecl*)(char*, void(__cdecl*)(unsigned), unsigned, short))0x00507DC0;
	auto eLoadStreamingSolidPack = (BOOL(__cdecl*)(char*, void(__cdecl*)(unsigned), unsigned, short))0x00507700;

    std::vector<std::string> streaming_geo_headers;
    std::vector<std::string> streaming_tex_headers;

    struct geometry_headers
    {
        const char* wheels = "CARS\\WHEELS\\GEOMETRY.BIN";
        const char* spoiler = "CARS\\SPOILER\\GEOMETRY.BIN";
        const char* spoiler_carerra = "CARS\\SPOILER_CARRERA\\GEOMETRY.BIN";
        const char* spoiler_hatch = "CARS\\SPOILER_HATCH\\GEOMETRY.BIN";
        const char* spoiler_porsches = "CARS\\SPOILER_PORSCHES\\GEOMETRY.BIN";
        const char* roof = "CARS\\ROOF\\GEOMETRY.BIN";
    } geometry_table;

    struct texture_headers
    {
        const char* textures = "CARS\\TEXTURES.BIN";
        const char* spoiler = "CARS\\WHEELS\\TEXTURES.BIN";
    } texture_table;

    void make_pack_writeout()
    {
        eLoadStreamingTexturePack((char*)texture_table.textures, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.spoiler, 0, 0, 0);

        for (const auto& header : streaming_tex_headers)
        {

            const auto& bin = "CARS\\" + header + "\\TEXTURES.BIN";
            auto ptr = (char*)bin.c_str();

            eLoadStreamingTexturePack(ptr, 0, 0, 0);

        }

        eLoadStreamingSolidPack((char*)geometry_table.wheels, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.spoiler, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.spoiler_carerra, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.spoiler_hatch, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.spoiler_porsches, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.roof, 0, 0, 0);

        for (const auto& header : streaming_geo_headers)
        {

            const auto& bin = "CARS\\" + header + "\\GEOMETRY.BIN";
            auto ptr = (char*)bin.c_str();

            eLoadStreamingSolidPack(ptr, 0, 0, 0);

        }
    }

    __declspec(naked) void detour_stream_packs()
    {
        __asm
        {

            pushad;
            call make_pack_writeout;
            popad;
            push 0x006649EB;
            retn;

        }
    }

    void load_streaming_headers(binary_reader* br, std::int32_t size)
    {
        br->advance(8);
        auto count = (size - 8) / 0xD0;

        for (std::int32_t i = 0; i < count; ++i)
        {

            auto cname = br->read_string(0x10);
            br->advance(0x40);
            auto key = br->read_uint32();
            br->advance(0x40);
            auto usage = br->read_int32();
            br->advance(0x38);

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

        utils::jump(0x00664957, detour_stream_packs);
    }

	void load_globalb_settings(const stdfs::path& file)
	{
        const auto filename = file.wstring();
        auto br = binary_reader(filename);
        if (!br) return;
        if (utils::is_compressed(&br)) return;

        while (br.position() < br.length())
        {

            const auto offset = br.position();
            const auto id = static_cast<bin_block_id>(br.read_uint32());
            const auto size = br.read_int32();

            if (id == bin_block_id::cartypeinfo)
            {

                load_streaming_headers(&br, size);

            }
            else if (id == bin_block_id::preset_rides)
            {

                //load_preset_rides(&br, size);

            }

            br.position(offset + size + 8);

        }
	}

	void process()
	{
		const auto& directory = stdfs::current_path().parent_path();
		const auto& globalb_path = directory / "GLOBAL" / "GLOBALB.LZC";

		load_globalb_settings(globalb_path);
	}
}
