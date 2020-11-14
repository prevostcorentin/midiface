#include "MemoryUtils.h"

const int MIDI::MemoryUtils::ToInteger(const std::vector<char>& bytes)
{
    // The most significant byte is the first so the most higher
    // power is at the beginning of the file cursor when
    // reading.
    unsigned int power = 0;
    int value = 0;
    for (int i = bytes.size() - 1; i >= 0; i--) {
        value = value + (bytes[i] << (power * 8));
        power = power + 1;
    }

    return value;
}
