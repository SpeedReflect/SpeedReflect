#include "pch.h"
#include "undercover.h"



namespace speedreflect::undercover
{
    auto eLoadStreamingSolidPack = (BOOL(__cdecl*)(char*, void(__cdecl*)(void*), void*, int, int))0x0053F370;
    auto eLoadStreamingTexturePack = (BOOL(__cdecl*)(char*, void(__cdecl*)(void*), void*, int, int))0x0053F620;

    std::uint8_t* vinylmetadata;
    std::vector<std::string> streaming_geo_headers;
    std::vector<std::string> streaming_tex_headers;

    struct vector_offset
    {
        std::uint32_t binkey;
        std::int32_t offset;
        std::int32_t size;
        float aspect_ratio;
    };

    struct geometry_headers
    {
        const char* brake = "CARS\\BRAKE\\GEOMETRY.BIN";
        const char* brakerotor = "CARS\\BRAKEROTOR\\GEOMETRY.BIN";
        const char* spoiler = "CARS\\SPOILER\\GEOMETRY.BIN";
        const char* roofscoop = "CARS\\ROOFSCOOP\\GEOMETRY.BIN";
        const char* seat = "CARS\\SEAT\\GEOMETRY.BIN";
        const char* whl_5zi = "CARS\\WHL_5ZI\\GEOMETRY.BIN";
        const char* whl_Adr = "CARS\\WHL_ADR\\GEOMETRY.BIN";
        const char* whl_Amr = "CARS\\WHL_AMR\\GEOMETRY.BIN";
        const char* whl_Are = "CARS\\WHL_ARE\\GEOMETRY.BIN";
        const char* whl_Bbs = "CARS\\WHL_BBS\\GEOMETRY.BIN";
        const char* whl_Cen = "CARS\\WHL_CEN\\GEOMETRY.BIN";
        const char* whl_Enk = "CARS\\WHL_ENK\\GEOMETRY.BIN";
        const char* whl_Hre = "CARS\\WHL_HRE\\GEOMETRY.BIN";
        const char* whl_Ifo = "CARS\\WHL_IFO\\GEOMETRY.BIN";
        const char* whl_Kin = "CARS\\WHL_KIN\\GEOMETRY.BIN";
        const char* whl_Kon = "CARS\\WHL_KON\\GEOMETRY.BIN";
        const char* whl_Low = "CARS\\WHL_LOW\\GEOMETRY.BIN";
        const char* whl_Ols = "CARS\\WHL_OLS\\GEOMETRY.BIN";
        const char* whl_Rch = "CARS\\WHL_RCH\\GEOMETRY.BIN";
        const char* whl_Roj = "CARS\\WHL_ROJ\\GEOMETRY.BIN";
        const char* whl_Sav = "CARS\\WHL_SAV\\GEOMETRY.BIN";
        const char* whl_Tdy = "CARS\\WHL_TDY\\GEOMETRY.BIN";
        const char* whl_Ten = "CARS\\WHL_TEN\\GEOMETRY.BIN";
        const char* whl_Tsw = "CARS\\WHL_TSW\\GEOMETRY.BIN";
        const char* whl_Vol = "CARS\\WHL_VOL\\GEOMETRY.BIN";
        const char* whl_Wel = "CARS\\WHL_WEL\\GEOMETRY.BIN";
        const char* whl_Wor = "CARS\\WHL_WOR\\GEOMETRY.BIN";
    } geometry_table;

    struct texture_headers
    {
        const char* textures = "CARS\\TEXTURES.BIN";
        const char* spoiler = "CARS\\SPOILER\\TEXTURES.BIN";
        const char* seat = "CARS\\SEAT\\TEXTURES.BIN";
        const char* brake = "CARS\\BRAKE\\TEXTURES.BIN";
        const char* brakerotor = "CARS\\BRAKEROTOR\\TEXTURES.BIN";
        const char* vinyls = "CARS\\VINYLS\\LIVERYTEXTURES.BIN";
        const char* whl_5zi = "CARS\\WHL_5ZI\\TEXTURES.BIN";
        const char* whl_Adr = "CARS\\WHL_ADR\\TEXTURES.BIN";
        const char* whl_Amr = "CARS\\WHL_AMR\\TEXTURES.BIN";
        const char* whl_Are = "CARS\\WHL_ARE\\TEXTURES.BIN";
        const char* whl_Bbs = "CARS\\WHL_BBS\\TEXTURES.BIN";
        const char* whl_Cen = "CARS\\WHL_CEN\\TEXTURES.BIN";
        const char* whl_Enk = "CARS\\WHL_ENK\\TEXTURES.BIN";
        const char* whl_Hre = "CARS\\WHL_HRE\\TEXTURES.BIN";
        const char* whl_Ifo = "CARS\\WHL_IFO\\TEXTURES.BIN";
        const char* whl_Kin = "CARS\\WHL_KIN\\TEXTURES.BIN";
        const char* whl_Kon = "CARS\\WHL_KON\\TEXTURES.BIN";
        const char* whl_Low = "CARS\\WHL_LOW\\TEXTURES.BIN";
        const char* whl_Ols = "CARS\\WHL_OLS\\TEXTURES.BIN";
        const char* whl_Rch = "CARS\\WHL_RCH\\TEXTURES.BIN";
        const char* whl_Roj = "CARS\\WHL_ROJ\\TEXTURES.BIN";
        const char* whl_Sav = "CARS\\WHL_SAV\\TEXTURES.BIN";
        const char* whl_Tdy = "CARS\\WHL_TDY\\TEXTURES.BIN";
        const char* whl_Ten = "CARS\\WHL_TEN\\TEXTURES.BIN";
        const char* whl_Tsw = "CARS\\WHL_TSW\\TEXTURES.BIN";
        const char* whl_Vol = "CARS\\WHL_VOL\\TEXTURES.BIN";
        const char* whl_Wel = "CARS\\WHL_WEL\\TEXTURES.BIN";
        const char* whl_Wor = "CARS\\WHL_WOR\\TEXTURES.BIN";
    } texture_table;

    void make_geo_writeout()
    {
        eLoadStreamingSolidPack((char*)geometry_table.brake, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.brakerotor, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.spoiler, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.roofscoop, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.seat, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_5zi, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Adr, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Amr, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Are, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Bbs, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Cen, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Enk, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Hre, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Ifo, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Kin, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Kon, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Low, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Ols, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Rch, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Roj, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Sav, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Tdy, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Ten, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Tsw, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Vol, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Wel, 0, 0, 0, 0);
        eLoadStreamingSolidPack((char*)geometry_table.whl_Wor, 0, 0, 0, 0);

        for (const auto& header : streaming_geo_headers)
        {

            const auto& bin = "CARS\\" + header + "\\GEOMETRY.BIN";
            auto ptr = (char*)bin.c_str();

            eLoadStreamingSolidPack(ptr, 0, 0, 0, 0);

        }
    }

    void make_tex_writeout()
    {
        eLoadStreamingTexturePack((char*)texture_table.textures, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.spoiler, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.seat, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.brake, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.brakerotor, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.vinyls, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_5zi, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Adr, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Amr, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Are, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Bbs, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Cen, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Enk, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Hre, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Ifo, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Kin, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Kon, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Low, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Ols, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Rch, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Roj, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Sav, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Tdy, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Ten, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Tsw, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Vol, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Wel, 0, 0, 0, 0);
        eLoadStreamingTexturePack((char*)texture_table.whl_Wor, 0, 0, 0, 0);

        for (const auto& header : streaming_tex_headers)
        {

            const auto& bin = "CARS\\" + header + "\\TEXTURES.BIN";
            auto ptr = (char*)bin.c_str();

            eLoadStreamingTexturePack(ptr, 0, 0, 0, 0);

        }
    }

    __declspec(naked) void detour_vinylmetadata()
    {
        __asm
        {

            mov eax, 0x00D5FFAC;
            mov ecx, vinylmetadata;
            add ecx, 8;
            mov[eax], ecx;
            mov eax, 0x00D5FFB0;
            mov ecx, 0x00D5F688;
            mov ecx, [ecx];
            mov[eax], ecx;
            push 0x0085E371;
            retn;

        }
    }

    __declspec(naked) void detour_stream_geo()
    {
        __asm
        {

            pushad;
            call make_geo_writeout;
            popad;
            push 0x00843EE3;
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
            push 0x00843F78;
            retn;

        }
    }

    void load_streaming_headers(binary_reader* br, std::int32_t size)
    {
        br->advance(8);
        auto count = (size - 8) / 0x130;

        for (std::int32_t i = 0; i < count; ++i)
        {

            auto cname = br->read_string(0x20);
            br->advance(0x90);
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

        utils::jump(0x00843EC0, detour_stream_geo);
        utils::jump(0x00843F51, detour_stream_tex);
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

            br.position(offset + size + 8);

        }
    }

    void load_vector_tables(const stdfs::path& file)
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
                        br.advance(8);
                        auto ratio = br.read_single();
                        vec_entries.push_back(vector_offset{ key, cur, (size + 8), ratio });
                        break;

                    }

                }

            }

            br.position(cur + size + 8);

        }

        auto total = vec_entries.size();
        auto table = reinterpret_cast<std::uint8_t*>(calloc(total, 12u));

        auto swap = [](vector_offset* x, vector_offset* y) -> void
        {
            auto temp = *x;
            *x = *y;
            *y = temp;
        };

        for (size_t i = 0; i < total - 1; i++)
        {

            for (size_t j = 0; j < total - i - 1; j++)
            {

                if (vec_entries[j].binkey > vec_entries[j + 1].binkey)
                {

                    swap(&vec_entries[j], &vec_entries[j + 1]);

                }

            }

        }

        vinylmetadata = reinterpret_cast<std::uint8_t*>(calloc(8 + (total << 3), 1));
        *reinterpret_cast<std::uint32_t*>(vinylmetadata) = (std::uint32_t)bin_block_id::vinylmetadata;
        *reinterpret_cast<std::int32_t*>(vinylmetadata + 4) = total << 3;

        for (size_t i = 0, j = 8, k = 0; i < total; ++i, j += 8, k += 12)
        {

            std::memcpy(&table[k], &vec_entries[i], 12u);
            *reinterpret_cast<std::uint32_t*>(vinylmetadata + j) = vec_entries[i].binkey;
            *reinterpret_cast<float*>(vinylmetadata + j + 4) = vec_entries[i].aspect_ratio;

        }

        utils::set(0x00D5F684, table);
        utils::set(0x00D5F688, total);
        utils::jump(0x0085E35C, detour_vinylmetadata);
    }

    void process()
    {
        const auto& directory = stdfs::current_path().parent_path();
        const auto& vinyls_path = directory / "CARS" / "VINYLS" / "VINYLS.BIN";
        const auto& globalb_path = directory / "GLOBAL" / "GLOBALB.LZC";

        load_vector_tables(vinyls_path);
        load_globalb_settings(globalb_path);
    }
}
