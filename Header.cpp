#include <istream>
#include <vector>

#include <MemoryUtils.h>
#include <Header.h>
#include <Stream.h>

MIDI::Header::Header(std::istream& stream)
{
    const std::streampos cursor_position = stream.tellg();
    stream.seekg(4, std::istream::beg);
    this->_length = MIDI::MemoryUtils::ReadToUnsignedInteger(stream, 4);
    this->_format = MIDI::MemoryUtils::ReadToUnsignedInteger(stream, 2);
    this->_tracks_count = MIDI::MemoryUtils::ReadToUnsignedInteger(stream, 2);
    this->_division = MIDI::MemoryUtils::ReadToUnsignedInteger(stream, 2);
    stream.seekg(cursor_position, std::istream::beg);
}

const MIDI::StreamFormat MIDI::Header::get_format()
{
    return MIDI::StreamFormat(this->_format);
}

const unsigned int MIDI::Header::get_length()
{
    return this->_length;
}

const unsigned int MIDI::Header::get_tracks_count()
{
    return this->_tracks_count;
}

const unsigned int MIDI::Header::get_division()
{
    return this->_division;
}
