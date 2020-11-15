#include <ImmutableStream.h>

MIDI::ImmutableStream::ImmutableStream(std::istream* stream_pointer) :
    _header(*stream_pointer)
{
    this->_stream.reset(stream_pointer);
}

std::vector<char> MIDI::ImmutableStream::read(const size_t size)
{
    std::istream* stream_pointer = this->_stream.get();
    const std::vector<char> data_read = MIDI::MemoryUtils::ReadStreamVector(*stream_pointer, size);

    return data_read;
}

MIDI::Header* MIDI::ImmutableStream::get_header()
{
    return &(this->_header);
}

const size_t MIDI::ImmutableStream::get_size()
{
    const std::streampos file_cursor_position = this->_stream->tellg();
    this->_stream->seekg(0, std::ios_base::end);
    const std::streampos file_size = this->_stream->tellg();
    this->_stream->seekg(file_cursor_position, std::ios_base::beg);

    return file_size;
}
