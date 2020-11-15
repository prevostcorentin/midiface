#pragma once

#include <istream>

#include <StreamFormat.h>


namespace MIDI
{
    class Header
    {
    public:
        Header(std::istream&);
        const StreamFormat get_format();
        const unsigned int get_length();
        const unsigned int get_tracks_count();
        const unsigned int get_division();
    private:
        unsigned int _format;
        unsigned int _length;
        unsigned int _tracks_count;
        unsigned int _division;
    };
}
