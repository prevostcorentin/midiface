#include "pch.h"
#include <Stream.h>
#include <ImmutableStream.h>
#include <StreamFactory.h>

#include <fstream>
#include <iostream>
#include <filesystem>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace MIDIFaceUnitTest
{
    namespace Fixtures
    {
        char TwoTracksData[] = { 'M', 'T', 'h', 'd', // 1: MIDI file header
                                0x00, 0x00, 0x00, 0x06, // 4: Length = 6
                                0x00, 0x01, // 8: Multi-track file
                                0x00, 0x02, // 10: 2 tracks
                                0x00, 96, // 12: 96 time per quarter note
                                'M', 'T', 'r', 'k', // 14: First track
                                0x00, 0x00, 0x00, 0x08, // 18: 8 bytes long
                                0x00, 0x00, 0x00, 0x00, // 22: Delta-time to 0
                                0x00, 0x00, 0x00, 0x00, // 26: Playing C0
                                'M', 'T', 'r', 'k', // 30: Second track
                                0x00, 0x00, 0x00, 0x08, // 34: 8 bytes long
                                0x00, 0x00, 0x00, 0x00, // 38: Delta-time to 0
                                0x00, 0x00, 0x00, 0x00 }; // 42: Playing C0
    }

	TEST_CLASS(MIDIStreamTest)
	{
	public:

        TEST_CLASS_INITIALIZE(MidiTestFileInitialization)
        {
            if (!std::filesystem::is_directory("./data"))
            {
                std::filesystem::create_directory("./data");
            }
            std::ofstream midi_file_stream("./data/test.midi", std::fstream::out | std::fstream::in | std::fstream::trunc);
            midi_file_stream.write(Fixtures::TwoTracksData, 46);
            midi_file_stream.flush();
            midi_file_stream.close();
        }

        TEST_METHOD(ImmutableStreamHeaderOk)
        {
            std::ifstream midi_stream("./data/test.midi", std::fstream::in);

            MIDI::ImmutableStream* stream = MIDI::StreamFactory::Create(midi_stream);
            MIDI::Header* header = stream->get_header();

            Assert::AreEqual(46, (signed int)stream->get_size());
            Assert::AreEqual(MIDI::StreamFormat::MultiTracks, header->get_format());
            Assert::AreEqual((unsigned int)96, header->get_division());
            Assert::AreEqual((unsigned int)2, header->get_tracks_count());
        }
	};
}
