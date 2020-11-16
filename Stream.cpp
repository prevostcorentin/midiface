#include <Stream.h>
#include <Spec.h>

#include <cstdio>
#include <cstring>

MIDI::Stream::~Stream()
{
    this->_stream.release();
}

std::ios* MIDI::Stream::get_stream()
{
    std::ios* _stream = this->_stream.get();
    return _stream;
}
