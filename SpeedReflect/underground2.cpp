#include "pch.h"
#include "underground2.h"
#include "ug2_progress.h"
#include <unordered_map>



namespace speedreflect::underground2
{
    bool is_gcareer_processed = false;
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

    void make_progress_writeout(char* career, char* stats)
    {
        auto stage = *reinterpret_cast<std::int32_t*>(career + 0x7AF8);
        std::printf("FillStatistics buildup - current stage: [%d]\n", stage);
        auto req = *reinterpret_cast<std::int32_t*>(0x007F7BB4 + stage * 0x10);
        std::printf("FillStatistics buildup - required DVD won: [%d]\n", req);
        *reinterpret_cast<std::int32_t*>(stats + 0x94) = req;
        *reinterpret_cast<float*>(stats + 0x30) = 0.0F;
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

    __declspec(naked) void detour_progress_bar()
    {
        __asm
        {

            push esi;
            push eax;
            call make_progress_writeout;
            add esp, 8;
            xor edx, edx;
            push 0x00528F41;
            retn;

        }
    }

    void init_progress_stats(binary_reader* br, block* stages, block* races, block* showcases)
    {
        auto progress = ug2_progress(br, races, showcases);

        for (const auto& pair : stages->key_to_offset)
        {

            if (pair.first == 0) continue;
            br->position(pair.second + 0x28);
            auto lastStageEvent = br->read_uint32();

            auto race_offset = races->get_offset_by_key(lastStageEvent);
            if (race_offset != -1) progress.race_chase(race_offset);
            progress.show_chase(pair.first);
            progress.write_to_table(pair.first);
            progress.clear();

        }

        utils::jump(0x00528F3C, detour_progress_bar);
    }

    void init_last_event(binary_reader* br, block* stages)
    {
        auto last = stages->get_offset_by_key(5);
        br->position(last + 0x28);
        auto lastStageEvent = br->read_uint32();
        std::printf("Last career event: [0x%08X]\n", lastStageEvent);

        utils::set<std::uint32_t>(0x00513AD4, lastStageEvent); // PlayerCareerState::CalcShowPostRaceMovie
        utils::set<std::uint32_t>(0x00513ADB, lastStageEvent); // PlayerCareerState::CalcShowPostRaceMovie
        utils::set<std::uint32_t>(0x00527C94, lastStageEvent); // EventPile::GetRandomEvent
        utils::set<std::uint32_t>(0x00527DDE, lastStageEvent); // PlayerCareerState::BuildListOfEvents
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

    void load_gcareer_settings(binary_reader* br, std::int32_t size)
    {
        auto races = block(bin_block_id::gcareer_races);
        auto showcases = block(bin_block_id::gshowcases);
        auto stages = block(bin_block_id::gcareer_stages);
        auto worldcs = block(bin_block_id::world_challenges);

        auto offset = br->position();
        std::printf("GCareer - Size: [0x%08X], Offset: [0x%08X]\n", size, offset);

        while (br->position() < offset + size)
        {

            auto id = static_cast<bin_block_id>(br->read_uint32());
            auto len = br->read_int32();
            auto cur = br->position();

            std::printf("Located ID [0x%08X] with offset [0x%08X] and size [0x%08X]\n", static_cast<std::int32_t>(id), cur, len);

            switch (id)
            {
            case speedreflect::bin_block_id::gcareer_races:
                races.offset = cur;
                races.size = len;
                races.lastpos = cur + len;
                break;

            case speedreflect::bin_block_id::gshowcases:
                showcases.offset = cur;
                showcases.size = len;
                showcases.lastpos = cur + len;
                break;
            
            case speedreflect::bin_block_id::gcareer_stages:
                stages.offset = cur;
                stages.size = len;
                stages.lastpos = cur + len;
                break;

            case speedreflect::bin_block_id::world_challenges:
                worldcs.offset = cur;
                worldcs.size = len;
                worldcs.lastpos = cur + len;
                break;

            default:
                break;
            }

            br->position(cur + len);

        }

        races.print();
        stages.print();
        showcases.print();
        worldcs.print();

        for (std::int32_t i = races.offset; i < races.lastpos; i += 0x88)
        {

            br->position(i + 8);
            auto key = br->read_uint32();
            races.key_to_offset[key] = i;

        }

        for (std::int32_t i = showcases.offset; i < showcases.lastpos; i += 0x40)
        {

            br->position(i + 0x20);
            auto key = br->read_uint32();
            showcases.key_to_offset[key] = i;

        }

        for (std::int32_t i = stages.offset; i < stages.lastpos; i += 0x50)
        {

            br->position(i);
            auto key = static_cast<std::uint32_t>(br->read_byte());
            stages.key_to_offset[key] = i;

        }

        std::printf("Located [%d] GCareerRaces...\n", races.key_to_offset.size());
        std::printf("Located [%d] GCareerStages...\n", stages.key_to_offset.size());
        std::printf("Located [%d] GShowcases...\n", showcases.key_to_offset.size());

        init_last_event(br, &stages);
        init_progress_stats(br, &stages, &races, &showcases);
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
            else if (id == bin_block_id::gcareer && !is_gcareer_processed)
            {

                load_gcareer_settings(&br, size);
                is_gcareer_processed = true;

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
        //utils::set<std::int8_t>(0x00527C62, 0x7F); // EventPile::GetRandomEvent

	}
}
