#include "WriteStream.h"
#include "Platform.h"
#include <math.h>


bool CWriteStream::SerializeInteger(int32_t val, int32_t min, int32_t max)
{
	MANGO_TRAP(min < max);
	MANGO_TRAP(val >= min);
	MANGO_TRAP(val <= max);

	// Shift to a unsigned value
	uint32_t uval = val - min;
	
	// Determine the # of required bits
	const int bits = bitsRequired(min, max);

	// Write bits
	SerializeBits(uval, bits);

	return true;
}

bool CWriteStream::SerializeBits(uint32_t val, const int bits)
{
	m_writer.WriteBits(val, bits);
	return true;
}

void CWriteStream::Flush()
{
	m_writer.FlushScratch();
}