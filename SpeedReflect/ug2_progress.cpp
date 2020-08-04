#include "pch.h"
#include "ug2_progress.h"



namespace speedreflect::underground2
{
    ug2_progress::ug2_progress(binary_reader* br, block* races, block* showcases)
    {
        this->br_ = br;
        this->races_ = races;
        this->showcases_ = showcases;
        this->requirement_ = stage_requirement();
    }

    void ug2_progress::clear()
    {
        this->requirement_.req_dvd_won = 0;
        this->requirement_.req_reg_won = 0;
        this->requirement_.req_url_won = 0;
        this->requirement_.req_spon_won = 0;
    }

    void ug2_progress::race_chase(std::int32_t offset)
    {
        if (!(*this->br_)) return;

        this->br_->position(offset);

        while (true)
        {

            this->br_->advance(0xC);
            unlock_method unlock;
            unlock.read(this->br_);
            auto condition = static_cast<unlock_type>(unlock.unlock_type);
            this->br_->advance(0x20);
            auto icon = static_cast<event_type>(this->br_->read_byte());

            if (icon == event_type::url) ++this->requirement_.req_url_won; // increase only if url

            switch (condition)
            {
            case unlock_type::specific_race_won:
                offset = this->races_->get_offset_by_key(unlock.unlock_condition.event_key);
                if (offset == -1) return;
                this->br_->position(offset);
                continue;

            case unlock_type::at_stage_start:
            case unlock_type::unknown_condition:
                return;

            case unlock_type::reg_races_won:
                this->requirement_.req_reg_won += unlock.unlock_condition.race_req.req_reg_races;
                return;

            case unlock_type::req_mult_won:
                this->requirement_.req_reg_won += unlock.unlock_condition.multi_req.req_reg_races;
                this->requirement_.req_spon_won += unlock.unlock_condition.multi_req.req_spon_races;
                this->requirement_.req_url_won += unlock.unlock_condition.multi_req.req_url_races;
                return;

            }
        }
    }

    void ug2_progress::show_chase(std::uint32_t stage)
    {
        for (const auto& pair : this->showcases_->key_to_offset)
        {

            this->br_->position(pair.second + 0x25);
            auto belongs = this->br_->read_byte();

            if (belongs == stage)
            {

                this->br_->advance(0xF);
                auto required = this->br_->read_boolean();
                if (required) ++this->requirement_.req_dvd_won;

            }

        }
    }

    void ug2_progress::write_to_table(std::uint32_t stage)
    {
        std::uint32_t address = 0x007F7BA8 + stage * 0x10;
        std::printf("Stage [%d], RequiredRegRacesWon: [%d] - address [0x%08X]\n", stage, this->requirement_.req_reg_won, address + 0x0);
        utils::set<std::int32_t>(address + 0x0, this->requirement_.req_reg_won);
        std::printf("Stage [%d], RequiredSponRacesWon: [%d] - address [0x%08X]\n", stage, this->requirement_.req_spon_won, address + 0x4);
        utils::set<std::int32_t>(address + 0x4, this->requirement_.req_spon_won);
        std::printf("Stage [%d], RequiredURLRacesWon: [%d] - address [0x%08X]\n", stage, this->requirement_.req_url_won, address + 0x8);
        utils::set<std::int32_t>(address + 0x8, this->requirement_.req_url_won);
        std::printf("Stage [%d], RequiredDVDRacesWon: [%d] - address [0x%08X]\n", stage, this->requirement_.req_dvd_won, address + 0xC);
        utils::set<std::int32_t>(address + 0xC, this->requirement_.req_dvd_won);
    }
}
