#ifndef MIDIFACE_MIDISTREAM_H
#define MIDIFACE_MIDISTREAM_H

#include <MIDIHeader.h>
#include <MIDITrack.h>

#include <memory>
#include <cstdio>
#include <cstddef>
#include <vector>

namespace MIDI
{
    enum class StreamType {
        Immutable, Continuous, Listening
    };

    class Stream
    {
    public:
        static std::unique_ptr<Stream> Create(StreamType stream_type, FileType file_type);
        virtual ~Stream() = 0;

        std::unique_ptr<std::ios> get_stream();
        virtual std::vector<std::byte> read(size_t size) = 0;
        virtual void rewind() = 0;
        virtual void move(signed int offset) = 0;
        virtual std::vector<Track> get_tracks();
    protected:
        std::unique_ptr<std::ios> stream;
    };

    class ImmutableStream : Stream
    {
    public:
        ImmutableStream(std::unique_ptr<std::istream>);
        ~ImmutableStream();

        std::vector<std::byte> read(size_t size);
        void rewind();
        void move(signed int offset);
    private:
        std::unique_ptr<std::istream> stream;
    };

    class ContinuousStream : Stream
    {
    public:
        ContinuousStream(std::unique_ptr<std::istream>);
        ~ContinuousStream();

        std::vector<std::byte> read(size_t size);
        void rewind();
        void move(signed int offset);
    private:
        std::unique_ptr<std::istream> stream;
    };

    class PipeStream : Stream
    {
    public:
        PipeStream(std::unique_ptr<std::iostream>);
        ~PipeStream();

        std::vector<std::byte> read(size_t size);
        void write(std::vector<std::byte>);
        void rewind();
        void move(signed int offset);
    };
}
#endif //MIDIFACE_MIDISTREAM_H
