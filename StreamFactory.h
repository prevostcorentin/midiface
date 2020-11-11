#pragma once

#include <fstream>
#include <ImmutableStream.h>

namespace MIDI
{
	class StreamFactory
	{
	public:
		/// <summary>
		/// Instantiates a <see cref="MIDI::Stream">MIDI::Stream</see> derived class from a file stream.
		/// </summary>
		/// <param name="file_stream"> - The C++ STL file stream</param>
		/// <returns>An ImmutableStream object</returns>
		static ImmutableStream* Create(std::ifstream& file_stream);
	};
}

