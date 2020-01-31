#ifndef _FILE_READER_H_
#define _FILE_READER_H_
#include "IFileReader.h"
#include <fstream>

class FileReader : public IFileReader {
public:
	FileReader(std::fstream &&file);
	std::string read(size_t num_read);
private:
	std::fstream _file;
};

#endif