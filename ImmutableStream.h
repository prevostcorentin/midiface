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

        std::vector<char> read(const size_t size);
        const std::streampos get_size();
        const StreamFormat get_format() override;
        const unsigned int get_division();
        std::vector<Track> get_tracks();
    private:
        std::unique_ptr<std::istream> stream;
    };
}
