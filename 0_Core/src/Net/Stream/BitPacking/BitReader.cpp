#include "BitReader.h"
#include "System/Debug/LogManager.h"
#include "Platform.h"

CBitReader::CBitReader(uint32_t* buffer, size_t bufferLen)
	: CBitPacker(buffer, bufferLen),
	m_numBitsRead(0),
	m_numBytesRead(0),
	m_totalBits(bufferLen * 8)
{
#ifdef BITPACKER_DEBUG_LOG
	log << "Bit reader running..";
	CLogManager::Instance().WriteLine(log.str());
	log.str("");
#endif
}

uint32_t CBitReader::ReadBits(const int bits)
{
	MANGO_TRAP(bits <= WORD_SIZE_IN_BITS);
	MANGO_TRAP(bits > 0);
	MANGO_TRAP(m_numBitsRead < m_totalBits);
	
#ifdef BITPACKER_DEBUG_LOG
	{
		log << "Reading in " << bits << " bits";
		CLogManager::Instance().WriteLine(log.str());
		log.str("");
	}

	{
		log << "Current scratch status: " << m_scratch << " [" << getBits(m_scratch, m_scratchBits) << "]";
		CLogManager::Instance().WriteLine(log.str());
		log.str("");
	}
#endif

	// IFF the number of bits requested for a read are
	// greater than the current number of bits in m_scratch,
	// we need to read more
	if (bits > m_scratchBits)
	{
		// We can ONLY read if the wordIndex is strictly less than the bufferLength
		MANGO_TRAP(m_numBytesRead < m_bufferLen);

#ifdef BITPACKER_DEBUG_LOG
		{
			log << "Reading in next word: " << m_buffer[m_wordIndex] << " [" << getBits(m_buffer[m_wordIndex], WORD_SIZE_IN_BITS) << "] -----";
			CLogManager::Instance().WriteLine(log.str());
			log.str("");
		}
#endif

		uint64_t nextWord = m_buffer[m_wordIndex];
		nextWord <<= m_scratchBits;

		m_scratch ^= nextWord;

		// Read in the next 32-bit number
		//m_scratch += m_buffer[m_wordIndex];

		m_scratchBits += WORD_SIZE_IN_BITS;

		// Increment word index and the number of bytes read
		m_wordIndex++;
		m_numBytesRead += WORD_SIZE_IN_BYTES;

#ifdef BITPACKER_DEBUG_LOG
		{
			log << "Scratch: " << m_scratch << " [" << getBits(m_scratch, m_scratchBits) << "]";
			CLogManager::Instance().WriteLine(log.str());
			log.str("");
		}
#endif

	}

#ifdef BITPACKER_DEBUG_LOG
	{
		log << "Scratch Bits: " << m_scratchBits;
		CLogManager::Instance().WriteLine(log.str());
		log.str("");
	}
#endif

	int remainingBits = m_scratchBits - bits;

	// Create mask
	uint64_t mask;
	mask = (1ULL << bits) - 1ULL;

	/* 
	* We want to grab the #<bits> most significant bits from m_scratch. This can be done by shifting
	* m_scratch right by the difference between the total number of bits in m_scratch (m_scratchBits) and
	* the number of bits we wish to grab (bits) [remainingBits]
	* Visual example:
	* bits = 3, m_scratchbits = 32, 
	* m_scratch = 11010101011011111010110101010010 [3580865874]
	* mask = 111 (7)
	* m_scratch >> 29 = 110
	* 110 & 111 = 110
	* => output = 110 [6]
	*/

	uint32_t output = m_scratch & mask;
	
	m_scratch >>= bits;

	// Set scratch to remaining
	m_scratchBits = remainingBits;

	// Increase the number of bits read
	m_numBitsRead += bits;

#ifdef BITPACKER_DEBUG_LOG
	{
		log << "READ DATA: " << output << " [" << getBits(output, bits) << "]";
		CLogManager::Instance().WriteLine(log.str());
		log.str("");
	}

	{
		log << "Current bits read: " << m_numBitsRead;
		CLogManager::Instance().WriteLine(log.str());
		log.str("");
	}
#endif

	return output;
}

bool CBitReader::WouldReadPastEnd(const int bits)
{
	return (m_numBitsRead + bits) > m_totalBits;
}
