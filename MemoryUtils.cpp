#include <istream>

#include <MemoryUtils.h>

const unsigned int MIDI::MemoryUtils::ReadToUnsignedInteger(std::istream& stream, const size_t size)
{
    const std::vector<char> data = MIDI::MemoryUtils::ReadStreamVector(stream, size);
    const unsigned int result = MIDI::MemoryUtils::VectorToUnsignedInteger(data);

    return result;
}

const std::vector<char> MIDI::MemoryUtils::ReadStreamVector(std::istream& stream, const size_t size)
{
    std::vector<char> data_read(size);
    std::streampos pos;
    for (unsigned int i = 0; i < size; i++)
    {
        data_read[i] = stream.get();
        pos = stream.tellg();
    }

    return data_read;
}

const unsigned int MIDI::MemoryUtils::VectorToUnsignedInteger(const std::vector<char>& bytes)
{
    unsigned int power = 0;
    unsigned int value = 0;
    // The most significant byte is the first so the most higher
    // power is at the beginning of the file cursor when
    // reading.
    for (int i = bytes.size() - 1; i >= 0; i--) {
        value = value + (bytes[i] << (power * 8));
        power = power + 1;
    }

    return value;
}
