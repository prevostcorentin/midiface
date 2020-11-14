#pragma once

#include <istream>
#include <memory>
#include <vector>

#include <Stream.h>

namespace MIDI
{
    class ListeningStream : public Stream
    {
    public:
        ListeningStream(std::istream*);
        ~ListeningStream();

        std::vector<char> read(size_t size) override;
        const StreamFormat get_format() override;
    private:
        std::unique_ptr<std::istream> stream;
    };
}
