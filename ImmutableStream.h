#pragma once

#include <Stream.h>

#include <istream>

namespace MIDI
{
    class ImmutableStream : public Stream
    { 
    public:
        ImmutableStream(std::istream*);

        std::vector<char> read(size_t size);
        void rewind();
        void move(signed int offset);
        std::streampos get_size();
        // StreamFormat get_format();
        // unsigned int get_division();
        // std::vector<Track> get_tracks();
    private:
        std::unique_ptr<std::istream> stream;
    };
}
