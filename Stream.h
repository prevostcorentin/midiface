#ifndef MIDIFACE_MIDISTREAM_H
#define MIDIFACE_MIDISTREAM_H

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
        static Stream* Create(std::streambuf &);
        static Stream* Create(std::streambuf *);
        static Stream* Create(std::unique_ptr<std::ios_base>);

        virtual ~Stream() = 0;

        std::unique_ptr<std::ios> get_stream();
        virtual std::vector<std::byte> read(size_t size) = 0;
        virtual void rewind() = 0;
        virtual void move(signed int offset) = 0;
        virtual unsigned int get_size();
        virtual unsigned int get_length();
        virtual StreamFormat get_format();
        virtual unsigned int get_division();
        virtual std::vector<Track> get_tracks();
    protected:
        std::unique_ptr<std::ios> stream;
    };

    class ImmutableStream : public Stream
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

    class ContinuousStream : public Stream
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

    class PipeStream : public Stream
    {
    public:
        PipeStream(std::iostream &);
        ~PipeStream();

        std::vector<std::byte> read(size_t size);
        void write(std::vector<std::byte>);
        void write(std::byte);
        void write(char);
        void rewind();
        void move(signed int offset);
    };
}
#endif //MIDIFACE_MIDISTREAM_H
