#pragma once

#include <cstdio>
#include <vector>

namespace MIDI
{
	namespace MemoryUtils
	{
		/// <summary>
		/// Read data as a vector
		/// </summary>
		/// <param name="stream"> - Reference to an input stream</param>
		/// <param name="size"> - Size of the read</param>
		/// <returns>A vector containing the data read</returns>
		const std::vector<char> ReadStreamVector(std::istream& stream, const size_t size);
		/// <summary>
		/// Transform data from a stream into integer
		/// </summary>
		/// <param name="stream"> - Reference to an input stream</param>
		/// <param name="size"> - Size of the read
		/// <returns>Data transformed to an integer</returns>
		const unsigned int ReadToUnsignedInteger(std::istream& stream, const size_t size);
		/// <summary>
		/// Transform data into integer
		/// </summary>
		/// <param name="data"> - Reference to a raw data container</param>
		/// <returns>Data transformed to an integer</returns>
		const unsigned int VectorToUnsignedInteger(const std::vector<char>& data);
	}
}

