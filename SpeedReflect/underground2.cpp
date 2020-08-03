#include "pch.h"
#include "underground2.h"



namespace speedreflect::underground2
{
    auto eLoadStreamingSolidPack = (int(__cdecl*)(char*, void(__cdecl*)(unsigned), unsigned, short))0x004941C0;
    auto eUnloadStreamingSolidPack = (int(__cdecl*)(char*, void(*)(unsigned), unsigned))0x004941F0;
    auto eHibernateStreamingSolidPack = (int(__cdecl*)(char*))0x0048DAE0;
    auto eUnhibernateStreamingSolidPack = (int(__cdecl*)(char*))0x0048DC60;

    std::vector<std::string> streaming_geo_headers;
    std::vector<std::string> streaming_tex_headers;

    struct geometry_headers
    {
        const char* exhaust = "CARS\\EXHAUST\\GEOMETRY.BIN";
        const char* brakes = "CARS\\BRAKES\\GEOMETRY.BIN";
        const char* mirrors_post = "CARS\\MIRRORS_POST\\GEOMETRY.BIN";
        const char* mirrors_body = "CARS\\MIRRORS_BODY\\GEOMETRY.BIN";
        const char* mirrors_suv = "CARS\\MIRRORS_SUV\\GEOMETRY.BIN";
        const char* mirrors_hummer = "CARS\\MIRRORS_HUMMER\\GEOMETRY.BIN";
        const char* spoiler = "CARS\\SPOILER\\GEOMETRY.BIN";
        const char* spoiler_hatch = "CARS\\SPOILER_HATCH\\GEOMETRY.BIN";
        const char* spoiler_suv = "CARS\\SPOILER_SUV\\GEOMETRY.BIN";
        const char* roof = "CARS\\ROOF\\GEOMETRY.BIN";
        const char* audio = "CARS\\AUDIO\\GEOMETRY.BIN";
    } geometry_table;

    void make_geo_writeout(int choice)
    {
        std::printf("Current executed handle streaming choice: [%d]\n", choice);

        if (choice == 1)
        {

            for (const auto& header : streaming_geo_headers)
            {

                std::printf("Loading file [%s]...\n", header.c_str());
                eLoadStreamingSolidPack((char*)header.c_str(), 0, 0, 0);
                std::printf("Finished loading file [%s]\n", header.c_str());

            }

        }
        else if (choice == 2)
        {

            for (const auto& header : streaming_geo_headers)
            {

                std::printf("Loading file [%s]...\n", header.c_str());
                eUnloadStreamingSolidPack((char*)header.c_str(), 0, 0);
                std::printf("Finished loading file [%s]\n", header.c_str());

            }

        }
        else if (choice == 3)
        {

            for (const auto& header : streaming_geo_headers)
            {

                std::printf("Loading file [%s]...\n", header.c_str());
                eHibernateStreamingSolidPack((char*)header.c_str());
                std::printf("Finished loading file [%s]\n", header.c_str());

            }

        }
        else if (choice == 4)
        {

            for (const auto& header : streaming_geo_headers)
            {

                std::printf("Loading file [%s]...\n", header.c_str());
                eUnhibernateStreamingSolidPack((char*)header.c_str());
                std::printf("Finished loading file [%s]\n", header.c_str());

            }

        }
    }

    __declspec(naked) void detour_stream_geo()
    {
        __asm
        {

            push ebx;
            call make_geo_writeout;
            add esp, 4;
            push 0x0057F103;
            retn;

        }
    }

	void load_streaming_headers(binary_reader* br, std::int32_t size)
	{
        br->advance(8);
        auto count = size / 0x890;

        for (std::int32_t i = 0; i < count; ++i)
        {

            auto cname = br->read_string(0x20);
            br->advance(0xB0);
            auto key = br->read_uint32();
            br->advance(0x770);
            auto usage = br->read_int32();
            br->advance(0x48);

            if (usage == 3)
            {

                streaming_tex_headers.push_back("CARS\\" + cname + "\\TEXTURES.BIN");
                streaming_geo_headers.push_back("CARS\\" + cname + "\\GEOMETRY.BIN");

            }
            else if (usage == 4)
            {

                streaming_geo_headers.push_back("CARS\\" + cname + "\\GEOMETRY.BIN");

            }

        }

        utils::jump(0x0057F0AC, detour_stream_geo);
	}

	void load_globalb_settings(const stdfs::path& file)
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

                load_streaming_headers(&br, size);

            }
            else if (id == bin_block_id::gcareer)
            {

                //

            }

            br.position(offset + size + 8);

        }

	}

    void init_vectors()
    {
        streaming_geo_headers.push_back(geometry_table.exhaust);
        streaming_geo_headers.push_back(geometry_table.brakes);
        streaming_geo_headers.push_back(geometry_table.mirrors_post);
        streaming_geo_headers.push_back(geometry_table.mirrors_body);
        streaming_geo_headers.push_back(geometry_table.mirrors_suv);
        streaming_geo_headers.push_back(geometry_table.mirrors_hummer);
        streaming_geo_headers.push_back(geometry_table.spoiler);
        streaming_geo_headers.push_back(geometry_table.spoiler_hatch);
        streaming_geo_headers.push_back(geometry_table.spoiler_suv);
        streaming_geo_headers.push_back(geometry_table.roof);
        streaming_geo_headers.push_back(geometry_table.audio);
    }

	void process()
	{
		const auto& directory = stdfs::current_path().parent_path();
		const auto& globalb_path = directory / "GLOBAL" / "GLOBALB.LZC";

        init_vectors();
		load_globalb_settings(globalb_path);

		utils::set<std::int8_t>(0x00500E2F, 0x7F); // AddUnlockedZone (ShopDataDesc)
		utils::set<std::int8_t>(0x00500E6F, 0x7F); // AddUnlockedZone (CareerEventData)
		utils::set<std::int8_t>(0x00500EB0, 0x7F); // AddUnlockedZone
		utils::set<std::int8_t>(0x00500F0B, 0x7F); // GetNextUnlockedTriggerZone
		utils::set<std::int8_t>(0x00500F1F, 0x7F); // GetNextUnlockedTriggerZone
		utils::set<std::int8_t>(0x0053345B, 0x7F); // PlayerCareerState::RecalcUnlockedZones
		utils::set<std::int8_t>(0x005334BB, 0x7F); // PlayerCareerState::RecalcUnlockedZones
		utils::set<std::int8_t>(0x0053352A, 0x7F); // PlayerCareerState::RecalcUnlockedZones
		utils::set<std::int8_t>(0x0053355B, 0x7F); // PlayerCareerState::RecalcUnlockedZones
		utils::set<std::int8_t>(0x0053362B, 0x7F); // PlayerCareerState::RecalcUnlockedZones
		utils::set<std::int32_t>(0x00500F38, 0x7F); // Reset
	}
}
