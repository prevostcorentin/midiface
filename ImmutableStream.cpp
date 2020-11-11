#include <ImmutableStream.h>

MIDI::ImmutableStream::ImmutableStream(std::istream* stream_pointer)
{
    this->stream.reset(stream_pointer);
}

std::vector<char> MIDI::ImmutableStream::read(size_t size)
{
    std::istream* data_stream = this->stream.get();
    std::vector<char> data_read(size);
    for (unsigned int i = 0; i < size; i++)
    {
        char c = data_stream->get();
        data_read.push_back(c);
        data_stream->seekg(1, std::ios_base::cur);
    }
    return data_read;
}

void MIDI::ImmutableStream::rewind()
{
    std::istream* data_stream = this->stream.get();
    data_stream->seekg(0, std::ios_base::beg);
}

void MIDI::ImmutableStream::move(signed int offset)
{
    std::istream* data_stream = this->stream.get();
    data_stream->seekg(offset);
}

std::streampos MIDI::ImmutableStream::get_size()
{
    std::istream* data_stream = this->stream.get();
    std::streampos file_cursor_position = data_stream->tellg();
    data_stream->seekg(0, std::ios_base::end);
    std::streampos file_size = data_stream->tellg();
    data_stream->seekg(file_cursor_position, std::ios_base::beg);
    return file_size;
}
