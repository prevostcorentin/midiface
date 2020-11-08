#ifndef MIDIFACE_MIDITRACK_H
#define MIDIFACE_MIDITRACK_H

namespace MIDI
{
    class Track
    {
    public:
        Track(unsigned int length);

        unsigned int get_length();
        Event get_event(unsigned int n);
    private:
        unsigned int length;
        std::vector<Event> events;
    }
}

#endif //MIDIFACE_MIDITRACK_H
