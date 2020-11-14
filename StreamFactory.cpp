#include "StreamFactory.h"

MIDI::ImmutableStream* MIDI::StreamFactory::Create(std::ifstream& file_stream)
{
    MIDI::ImmutableStream* immutable_stream = new MIDI::ImmutableStream(&file_stream);
    return immutable_stream;
}
