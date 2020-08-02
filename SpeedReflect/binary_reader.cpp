#include "pch.h"
#include "binary_reader.h"



namespace speedreflect
{
    binary_reader::binary_reader(std::wstring& filename)
    {
        this->is_ready_ = false;
        this->length_ = 0;
        this->position_ = 0;
        this->handle_ = nullptr;

        if (!stdfs::exists(filename)) return;

        this->filename_ = filename;
        if (_wfopen_s(&this->handle_, filename.c_str(), L"rb") || !this->handle_) return;

        struct _stat32 stat32;
        if (_wstat32(filename.c_str(), &stat32)) return;

        this->length_ = stat32.st_size;
        this->is_ready_ = true;
    }

    binary_reader::~binary_reader()
    {
        if (!this) return;
        else fclose(this->handle_);
    }

    binary_reader::operator bool() const
    {
        return this->is_ready_ && this->handle_;
    }

    void binary_reader::check_space(size_t size)
    {
        if (this->position_ + (std::int32_t)size > this->length_)
        {

            throw std::exception("Unable to read beyond stream size");

        }
    }

    void binary_reader::read(void* dest, size_t size)
    {
        this->check_space(size);
        fread_s(dest, size, 1, size, this->handle_);
        this->position_ += size;
    }

    template <typename t> void binary_reader::read(t* object)
    {
        auto size = sizeof(t);
        this->check_space(size);
        fread_s(object, size, size, 1, this->handle_);
        this->position_ += size;
    }

    bool binary_reader::read_boolean()
    {
        std::int8_t result;
        this->check_space(sizeof(std::int8_t));
        fread_s(&result, sizeof(std::int8_t), sizeof(std::int8_t), 1, this->handle_);
        this->position_ += sizeof(std::int8_t);
        return result != 0;
    }

    std::int8_t binary_reader::read_char()
    {
        std::int8_t result;
        this->check_space(sizeof(std::int8_t));
        fread_s(&result, sizeof(std::int8_t), sizeof(std::int8_t), 1, this->handle_);
        this->position_ += sizeof(std::int8_t);
        return result;
    }

    std::uint8_t binary_reader::read_byte()
    {
        std::uint8_t result;
        this->check_space(sizeof(std::uint8_t));
        fread_s(&result, sizeof(std::uint8_t), sizeof(std::uint8_t), 1, this->handle_);
        this->position_ += sizeof(std::uint8_t);
        return result;
    }

    std::int16_t binary_reader::read_int16()
    {
        std::int16_t result;
        this->check_space(sizeof(std::int16_t));
        fread_s(&result, sizeof(std::int16_t), sizeof(std::int16_t), 1, this->handle_);
        this->position_ += sizeof(std::int16_t);
        return result;
    }

    std::uint16_t binary_reader::read_uint16()
    {
        std::uint16_t result;
        this->check_space(sizeof(std::uint16_t));
        fread_s(&result, sizeof(std::uint16_t), sizeof(std::uint16_t), 1, this->handle_);
        this->position_ += sizeof(std::uint16_t);
        return result;
    }

    std::int32_t binary_reader::read_int32()
    {
        std::int32_t result;
        this->check_space(sizeof(std::int32_t));
        fread_s(&result, sizeof(std::int32_t), sizeof(std::int32_t), 1, this->handle_);
        this->position_ += sizeof(std::int32_t);
        return result;
    }

    std::uint32_t binary_reader::read_uint32()
    {
        std::uint32_t result;
        this->check_space(sizeof(std::uint32_t));
        fread_s(&result, sizeof(std::uint32_t), sizeof(std::uint32_t), 1, this->handle_);
        this->position_ += sizeof(std::uint32_t);
        return result;
    }

    std::int64_t binary_reader::read_int64()
    {
        std::int64_t result;
        this->check_space(sizeof(std::int64_t));
        fread_s(&result, sizeof(std::int64_t), sizeof(std::int64_t), 1, this->handle_);
        this->position_ += sizeof(std::int64_t);
        return result;
    }

    std::uint64_t binary_reader::read_uint64()
    {
        std::uint64_t result;
        this->check_space(sizeof(std::uint64_t));
        fread_s(&result, sizeof(std::uint64_t), sizeof(std::uint64_t), 1, this->handle_);
        this->position_ += sizeof(std::uint64_t);
        return result;
    }

    float binary_reader::read_single()
    {
        float result;
        this->check_space(sizeof(float));
        fread_s(&result, sizeof(float), sizeof(float), 1, this->handle_);
        this->position_ += sizeof(float);
        return result;
    }

    double binary_reader::read_double()
    {
        double result;
        this->check_space(sizeof(double));
        fread_s(&result, sizeof(double), sizeof(double), 1, this->handle_);
        this->position_ += sizeof(double);
        return result;
    }

    std::string binary_reader::read_string()
    {
        std::string result = empty;

        while (this->position_ < this->length_)
        {

            std::int8_t c;
            fread_s(&c, sizeof(std::int8_t), sizeof(std::int8_t), 1, this->handle_);
            this->position_ += sizeof(std::int8_t);
            if (c == 0) break;
            else result += c;

        }

        return result;
    }

    std::string binary_reader::read_string(std::int32_t maxlen)
    {
        std::string result = empty;
        auto max = this->position_ + maxlen;
        if (this->length_ < max) max = this->length_;

        while (this->position_ < max)
        {

            std::int8_t c;
            fread_s(&c, sizeof(std::int8_t), sizeof(std::int8_t), 1, this->handle_);
            this->position_ += sizeof(std::int8_t);
            if (c == 0) break;
            else result += c;

        }

        return result;
    }

    std::wstring binary_reader::path()
    {
        return this->filename_;
    }

    std::int32_t binary_reader::length()
    {
        return this->length_;
    }

    std::int32_t binary_reader::position()
    {
        return this->position_;
    }

    void binary_reader::position(std::int32_t at)
    {
        fseek(this->handle_, at, SEEK_SET);
        this->position_ = at;
    }
}
