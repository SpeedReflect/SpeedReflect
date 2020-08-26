#include "pch.h"
#include "carbon.h"
#include <set>



namespace speedreflect::carbon
{
    auto HandleCarStreamingSolidHeader = (BOOL(__cdecl*)(char*, int, int, short))0x0055F670;
    auto eLoadStreamingTexturePack = (BOOL(__cdecl*)(char*, void(__cdecl*)(void*), int, short))0x0055F850;

    std::uint8_t* vinylhashtable;
    std::vector<std::string> streaming_geo_headers;
    std::vector<std::string> streaming_tex_headers;

    struct vector_offset
    {
        std::uint32_t binkey;
        std::int32_t offset;
        std::int32_t size;
    };

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

            HandleCarStreamingSolidHeader(ptr, 0, 0, 0);

        }
    }

    void make_tex_writeout()
    {
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

            eLoadStreamingTexturePack(ptr, 0, 0, 0);

        }
    }

    __declspec(naked) void detour_vinylhashtable()
    {
        __asm
        {

            mov eax, 0x00B74D98;
            mov ebx, vinylhashtable;
            add ebx, 0x10;
            mov [eax], ebx;
            push 0x007C6A6A;
            retn;

        }
    }

    __declspec(naked) void detour_stream_geo1()
    {
        __asm
        {

            pushad;
            call make_geo_writeout;
            popad;
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

            pushad;
            call make_geo_writeout;
            popad;

        quit:
            push 0x007B14DD;
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
            push 0x007B1522;
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

        utils::jump(0x007B1880, detour_stream_geo1);
        utils::jump(0x007B14BB, detour_stream_geo2);
        utils::jump(0x007B1501, detour_stream_tex);
    }

    void load_vinyl_table(binary_reader* br, std::int32_t size)
    {
        auto ptr = *reinterpret_cast<vector_offset**>(0x00A7AAD4);
        auto count = *reinterpret_cast<std::int32_t*>(0x00A7AAD8);
        auto last = br->position() + size;

        auto hashheader = block(bin_block_id::vinylhashheader);
        auto carentries = block(bin_block_id::vinylcarentries);
        auto floatmatrix = block(bin_block_id::vinylfloatmatrix);
        auto vectorentry = block(bin_block_id::vinylvectorentry);

        while (br->position() < last)
        {

            auto cur = br->position();
            auto id = static_cast<bin_block_id>(br->read_uint32());
            auto len = br->read_int32();

            switch (id)
            {
            case bin_block_id::vinylhashheader:
                hashheader.offset = cur;
                hashheader.size = len;
                hashheader.lastpos = hashheader.offset + hashheader.size;
                break;

            case bin_block_id::vinylcarentries:
                carentries.offset = cur;
                carentries.size = len;
                carentries.lastpos = hashheader.offset + hashheader.size;
                break;

            case bin_block_id::vinylfloatmatrix:
                floatmatrix.offset = cur;
                floatmatrix.size = len;
                floatmatrix.lastpos = hashheader.offset + hashheader.size;
                break;

            case bin_block_id::vinylvectorentry:
                for (std::int32_t i = 0; i < (len >> 3); ++i)
                {

                    auto key = br->read_uint32();
                    auto set = br->read_uint32();
                    vectorentry.key_to_offset[key] = set;

                }
                break;

            default:
                break;

            }

            br->position(cur + len + 8);

        }

        std::set<std::uint32_t> binkeys;

        for (int i = 0; i < count; ++i)
        {

            auto entry = *reinterpret_cast<vector_offset*>(ptr + i);
            binkeys.insert(entry.binkey);

        }

        std::int32_t headoff = 8;
        std::int32_t caroff = headoff + 8 + hashheader.size;
        std::int32_t floatoff = caroff + 8 + carentries.size;
        std::int32_t vectoroff = floatoff + 8 + floatmatrix.size;
        std::int32_t total = vectoroff + 8 + (binkeys.size() << 3);

        vinylhashtable = reinterpret_cast<std::uint8_t*>(calloc(total, 1));
        *reinterpret_cast<std::uint32_t*>(vinylhashtable) = (std::uint32_t)bin_block_id::vinylhashtable;
        *reinterpret_cast<std::int32_t*>(vinylhashtable + 4) = total - 8;

        br->position(hashheader.offset);
        br->read(&vinylhashtable[headoff], hashheader.size + 8);
        br->position(carentries.offset);
        br->read(&vinylhashtable[caroff], carentries.size + 8);
        br->position(floatmatrix.offset);
        br->read(&vinylhashtable[floatoff], floatmatrix.size + 8);
        
        *reinterpret_cast<std::uint8_t**>(&vinylhashtable[headoff + 0x10]) = &vinylhashtable[caroff + 8];
        *reinterpret_cast<std::uint8_t**>(&vinylhashtable[headoff + 0x14]) = &vinylhashtable[floatoff + 8];
        *reinterpret_cast<std::uint32_t*>(&vinylhashtable[headoff + 0x1C]) = binkeys.size();
        *reinterpret_cast<std::uint8_t**>(&vinylhashtable[headoff + 0x20]) = &vinylhashtable[vectoroff + 8];
        *reinterpret_cast<std::uint32_t*>(&vinylhashtable[vectoroff]) = (std::uint32_t)bin_block_id::vinylvectorentry;
        *reinterpret_cast<std::int32_t*>(&vinylhashtable[vectoroff + 4]) = binkeys.size() << 3;

        binkeys.clear();

        for (int i = 0, j = 0; i < count; ++i)
        {

            auto pos = &vinylhashtable[vectoroff + ((j + 1) << 3)];
            auto entry = *reinterpret_cast<vector_offset*>(ptr + i);

            if (binkeys.find(entry.binkey) != binkeys.end()) continue;
            else { binkeys.insert(entry.binkey); ++j; }

            auto set = vectorentry.get_offset_by_key(entry.binkey);
            *reinterpret_cast<std::uint32_t*>(pos) = entry.binkey;
            *reinterpret_cast<std::uint32_t*>(pos + 4) = set;

        }

        utils::jump(0x007C6A5C, detour_vinylhashtable);
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
            else if (id == bin_block_id::vinylhashtable)
            {

                load_vinyl_table(&br, size);

            }

            br.position(offset + size + 8);

        }
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
    }

    void unlock_memory_files()
    {
        // don't use memory files.
        utils::set<std::uint8_t>(0x006B6A51, 0xEB); // InGameMemoryFile
        utils::set<std::uint8_t>(0x006B6D4F, 0xEB); // GlobalMemoryFile
        utils::set<std::uint8_t>(0x006B7044, 0xEB); // GlobalMemoryFile
    }

    void process()
    {
        const auto& directory = stdfs::current_path().parent_path();
        const auto& vinyls_path = directory / "CARS" / "VINYLS" / "VINYLS.BIN";
        const auto& logos_path = directory / "FRONTEND" / "LOGOS.BIN";
        const auto& globalb_path = directory / "GLOBAL" / "GLOBALB.LZC";

        make_vectors(vinyls_path, 0x00A7AAD4, 0x00A7AAD8);
        make_vectors(logos_path, 0x00A71250, 0x00A71254);
        load_globalb_settings(globalb_path);
        //unlock_memory_files();
    }
}
