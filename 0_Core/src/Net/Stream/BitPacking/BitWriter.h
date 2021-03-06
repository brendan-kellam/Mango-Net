#ifndef BITWRITER_H
#define BITWRITER_H

#include <sstream>
#include "BitPacker.h"


class MANGO_API CBitWriter
	: public CBitPacker
{

private:
	std::ostringstream log;

	// The number of bytes written to uint32_t* m_buffer
	int m_numBytesWritten;

public:
	
	
	//************************************
	// Method:    BitWriter
	// FullName:  CBitWriter::BitWriter
	// Access:    public 
	// Parameter: uint32_t * buffer - Data buffer
	// Parameter: size_t bufferLen - Size of buffer (IN BYTES)
	//************************************
	CBitWriter(uint32_t* buffer, size_t bufferLen);

	
	~CBitWriter() override;

	void WriteBits(uint32_t data, const int bits);


	//************************************
	// Method:    FlushScratch
	// FullName:  CBitWriter::FlushScratch
	// Access:    public 
	// Returns:   void
	// Notes:	  Flushes any remaining data from scratch into m_buffer
	//************************************
	void FlushScratch();
};


#endif