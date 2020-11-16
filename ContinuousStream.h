#pragma once

#include <istream>
#include <memory>
#include <vector>

#include <Stream.h>


namespace MIDI
{
    class ContinuousStream : public Stream
    {
    public:
        ContinuousStream(std::unique_ptr<std::istream>);
        ~ContinuousStream();

        std::vector<char> read(size_t size) override;
    private:
        std::unique_ptr<std::istream> _stream;
    };
}
