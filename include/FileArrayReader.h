#ifndef _FILE_BLOCK_READER_H_
#define _FILE_BLOCK_READER_H_
#include "IBlockBuffer.h"
#include <vector>
#include <fstream>

class FileArrayReader : public IBlockBuffer<std::vector<int>> {
public:
	FileArrayReader(std::ifstream &&file);
	~FileArrayReader();
    size_t next(std::vector<int> &buff_ptr, size_t block_read) override;
    void close();

private:
    std::ifstream _file;
};

#endif
