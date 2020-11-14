#pragma once

#include <Header.h>
#include <Track.h>

#include <memory>
#include <cstdio>
#include <cstddef>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstddef>


namespace MIDI
{
    enum class StreamType {
        Immutable, Continuous, Listening
    };
    
    enum class StreamFormat {
        UniqueTrack = 0, MultiTracks = 1, SequentiallyIndependantTracks = 2
    };

    class Stream
    {
    public:
        virtual ~Stream();

        std::ios* get_stream();
        virtual std::vector<char> read(size_t size) = 0;
        virtual const StreamFormat get_format() = 0;
    protected:
        std::unique_ptr<std::ios> stream;
    };
}
