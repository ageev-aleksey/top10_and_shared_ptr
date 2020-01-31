#include "shared_ptr.h"
#ifndef _IBLOCK_BUFFER_
#define _IBLOCK_BUFFER_

template<typename BlockType>
class IBlockBuffer {
public:
	virtual size_t next(BlockType &buff_ptr, size_t block_read) = 0;
	virtual ~IBlockBuffer() {}
};

#endif
