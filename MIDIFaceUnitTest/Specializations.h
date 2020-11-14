#pragma once

#include "CppUnitTest.h"

#include <string>
#include <Stream.h>

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<> static std::wstring ToString<MIDI::StreamFormat>(const enum MIDI::StreamFormat& format)
            {
                std::wstring message;
                if (format == MIDI::StreamFormat::UniqueTrack)
                {
                    message = L"Unique track mode";
                }
                else if (format == MIDI::StreamFormat::MultiTracks)
                {
                    message = L"Multi track mode";
                }
                else if (format == MIDI::StreamFormat::SequentiallyIndependantTracks)
                {
                    message = L"Sequentially independant tracks";
                }
                return message;
            }
        }
    }
}