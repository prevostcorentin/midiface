#include <ImmutableStream.h>

MIDI::ImmutableStream::ImmutableStream(std::istream* stream_pointer)
{
    this->stream.reset(stream_pointer);
}

std::vector<char> MIDI::ImmutableStream::read(const size_t size)
{
    std::vector<char> data_read(size);
    std::streampos pos;
    for (unsigned int i = 0; i < size; i++)
    {
        data_read[i] = this->stream->get();
        pos = this->stream->tellg();
    }
    return data_read;
}

const std::streampos MIDI::ImmutableStream::get_size()
{
    const std::streampos file_cursor_position = this->stream->tellg();
    this->stream->seekg(0, std::ios_base::end);
    const std::streampos file_size = this->stream->tellg();
    this->stream->seekg(file_cursor_position, std::ios_base::beg);
    return file_size;
}

const MIDI::StreamFormat MIDI::ImmutableStream::get_format()
{
    const std::streampos cursor_position = this->stream->tellg();
    this->stream->seekg(8, std::istream::beg);
    const std::vector<char> data = this->read(2);
    const int format = MIDI::MemoryUtils::ToInteger(data);
    this->stream->seekg(cursor_position, std::istream::beg);

    return StreamFormat(format);
}

const unsigned int MIDI::ImmutableStream::get_division()
{
    const std::streampos cursor_position = this->stream->tellg();
    this->stream->seekg(12, std::istream::beg);
    const std::vector<char> data = this->read(2);
    const int division = MIDI::MemoryUtils::ToInteger(data);
    this->stream->seekg(cursor_position, std::istream::beg);

    return division;
}
