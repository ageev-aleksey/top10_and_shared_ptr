#include "FileReader.h"


FileReader::FileReader(std::fstream &&file) : _file(std::move(file))
{}

std::string FileReader::read(size_t num_read) {
    char *tmp  = new char[num_read];
	_file.read(tmp, num_read);
	return std::string(tmp);
}
