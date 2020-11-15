#pragma once

#include <istream>
#include <vector>

#include <MemoryUtils.h>
#include <Stream.h>
#include <Track.h>

namespace MIDI
{
    class ImmutableStream : public Stream
    { 
    public:
        ImmutableStream(std::istream*);

        std::vector<char> read(const size_t size) override;
        const size_t get_size();
        Header* get_header();
    private:
        std::unique_ptr<std::istream> _stream;
        MIDI::Header _header;
    };
}
