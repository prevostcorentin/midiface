#ifndef MIDIFACE_MIDITRACK_H
#define MIDIFACE_MIDITRACK_H

#include <vector>

#include <Event.h>

namespace MIDI
{
    class Track
    {
    public:
        Track(unsigned int length);

        unsigned int get_length();
        TrackEvent get_event(unsigned int n);
    private:
        unsigned int length;
        std::vector<TrackEvent> events;
    };
}

#endif //MIDIFACE_MIDITRACK_H
