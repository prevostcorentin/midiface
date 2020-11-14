#pragma once

#include <cstdio>
#include <vector>

namespace MIDI
{
	namespace MemoryUtils
	{
		/// <summary>
		/// Transform data in integer
		/// </summary>
		/// <param name="data"> - Reference to a raw data container</param>
		/// <returns>Data transformed to an integer</returns>
		const int ToInteger(const std::vector<char>& data);
	}
}

