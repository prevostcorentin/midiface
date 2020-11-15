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

    class Stream
    {
    public:
        virtual ~Stream();

        std::ios* get_stream();
        virtual std::vector<char> read(size_t size) = 0;
    protected:
        std::unique_ptr<std::ios> _stream;
    };
}
