#pragma once

#include "types.h"



namespace speedreflect::underground2
{

	class ug2_progress
	{
    private:
        struct stage_requirement
        {
            std::int32_t req_reg_won;
            std::int32_t req_spon_won;
            std::int32_t req_url_won;
            std::int32_t req_dvd_won;
        };
        struct unlock_method
        {
            union uni
            {
                struct multi
                {
                    std::int8_t none;
                    std::int8_t req_reg_races;
                    std::int8_t req_spon_races;
                    std::int8_t req_url_races;
                };
                struct race
                {
                    std::int16_t none;
                    std::int8_t req_reg_races;
                    std::int8_t pad;
                };
                std::uint32_t event_key;
                race race_req;
                multi multi_req;
            };
            std::int8_t unlock_type;
            std::int8_t padding[3];
            uni unlock_condition;
            void read(binary_reader* br)
            {
                this->unlock_type = br->read_char();
                br->advance(3);
                this->unlock_condition.event_key = br->read_uint32();
            }
        };
        enum class unlock_type : std::uint8_t
        {
            specific_race_won = 0,
            at_stage_start = 1,
            unknown_condition = 2,
            reg_races_won = 3,
            req_mult_won = 4,
        };
        enum class event_type : std::uint8_t
        {
            none = 0,
            sponsor = 1,
            url = 2,
            regular = 3,
        };

    public:
        ug2_progress(binary_reader* br, block* races, block* showcases);
        void race_chase(std::int32_t offset);
        void stage_chase(std::uint32_t stage);
        void show_chase(std::uint32_t stage);
        void write_to_table(std::uint32_t stage);
        void clear();

    private:
        binary_reader* br_;
        block* races_;
        block* showcases_;
        stage_requirement requirement_;
	};

}
