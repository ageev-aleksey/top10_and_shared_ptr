#include <algorithm>
#include <fstream>
#include <iostream>
#include "FileArrayReader.h"
#include "IBlockBuffer.h"
#include "ExtractTopN.h"

int main() {
    std::ifstream file1(std::string(RESOURCES_DIRECTORY) + std::string("/array2.txt"));
    std::ifstream file2(std::string(RESOURCES_DIRECTORY) + std::string("/array2.txt"));
    if(file1.is_open() && file2.is_open()) {
        FileArrayReader f1(std::move(file1));
        std::shared_ptr<IBlockBuffer<std::vector<int>>> fptr = std::make_shared<FileArrayReader >(std::move(file2));
        std::vector<int> buff;
        f1.next(buff, 1000000);
        std::sort(buff.begin(), buff.end(), std::greater<>{});
        std::vector<int> res = ExtractTopN(fptr, 10, 10000);
        std::cout << "size of result array: " << res.size() << std::endl;
        std::sort(res.begin(), res.end(), std::greater<>{});
		std::cout << "Result: ";
        for(auto itr = res.begin(); itr !=  res.end() ; itr++) {
            std::cout << *itr << " ";
        }
        std::cout << std::endl << "Correct answer: ";
        for(auto itr = buff.begin(); itr !=  buff.begin()+10 ; itr++) {
            std::cout << *itr << " ";
        }
		std::cout << std::endl;
		for (size_t i = 0; i < res.size(); i++) {
			if (res[i] != buff[i]) {
				std::cout << "ERROR: " << "res[" << i << "] != buff[" << i << "];\n";
			}
		}
    } else {
        std::cout << "files not opened\n";
    }

}