//
// Created by Aleksey on 31.01.2020.
//

#ifndef SHARED_PTR_IFILEREADER_H
#define SHARED_PTR_FILEREADER_H
#include <fstream>
#include <string>

class IFileReader {
public:
    virtual std::string read(size_t num_read) = 0;
private:

};



#endif //SHARED_PTR_IFILEREADER_H
