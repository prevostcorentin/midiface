#pragma once


namespace MIDI
{
    enum class StreamFormat {
        UniqueTrack = 0, MultiTracks = 1, SequentiallyIndependantTracks = 2
    };
}