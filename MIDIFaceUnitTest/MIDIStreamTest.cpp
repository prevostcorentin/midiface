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
        char TwoTracksHeader[] = { 'M', 'T', 'h', 'd', // 1: MIDI file header
                                   0x00, 0x00, 0x00, 0x06, // 4: Length = 6
                                   0x00, 0x01, // 6: Multi-track file
                                   0x00, 0x02, // 8: 2 tracks
                                   0x00, 96 };  // 10: division 96

        char TwoTracksData[] = { 'M', 'T', 'h', 'd', // 1: MIDI file header
                                0x00, 0x00, 0x00, 0x06, // 4: Length = 6
                                0x00, 0x01, // 8: Multi-track file
                                0x00, 0x02, // 12: 2 tracks
                                0x00, 96, // 16: 96 time per quarter note
                                'M', 'T', 'r', 'k', // 20: First track
                                0x00, 0x00, 0x00, 0x08, // 24: 8 bytes long
                                0x00, 0x00, 0x00, 0x00, // 28: Delta-time to 0
                                0x00, 0x00, 0x00, 0x00, // 32: Playing C0
                                'M', 'T', 'r', 'k', // 36: Second track
                                0x00, 0x00, 0x00, 0x08, // 40: 8 bytes long
                                0x00, 0x00, 0x00, 0x00, // 44: Delta-time to 0
                                0x00, 0x00, 0x00, 0x00 }; // 48: Playing C0
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
            
            Assert::AreEqual(46, (signed int)stream->get_size());
            Assert::AreEqual(MIDI::StreamFormat::MultiTracks, stream->get_format());
            Assert::AreEqual((unsigned int)96, stream->get_division());
        }

        TEST_METHOD(ImmutableStreamTracksNumber)
        {
            std::ifstream file_stream("data/test.midi");

            MIDI::ImmutableStream* stream = MIDI::StreamFactory::Create(file_stream);

            Assert::IsFalse(true, L"Asserts not implemented");
            /*std::vector<MIDI::Track> tracks = stream->get_tracks();

            Assert::AreEqual(tracks[0].get_length(), (unsigned int)8);
            Assert::AreEqual(tracks[1].get_length(), (unsigned int)8);*/
        }
	};
}
