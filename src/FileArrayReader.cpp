#include "FileArrayReader.h"

#include <utility>
#include <string>
#include <stdexcept>
#include <iostream>



size_t FileArrayReader::next(std::vector<int> &buff_ptr, size_t block_read) {
    size_t readed = 0;
    for(size_t i = 0; i < block_read; i++) {
        std::string res;
        char tmp = '\0';
		_file.get(tmp);
        while(tmp != ' ' && !_file.eof()) {
			res.push_back(tmp);
			_file.get(tmp);
        }
		if (res.size() == 0) {
			break;
		}
		try {
			buff_ptr.push_back(std::stoi(res));
		}
		catch (std::exception &exp) {
			std::cout << exp.what() << std::endl;
		}
        
		

		readed++;
        if(_file.eof()) {
            break;
        }
		
    }
    return readed;
}

FileArrayReader::FileArrayReader(std::ifstream &&file) {
    _file = std::move(file);
}

void FileArrayReader::close() {
    if(_file.is_open()) _file.close();
}

FileArrayReader::~FileArrayReader() {
    close();
}
