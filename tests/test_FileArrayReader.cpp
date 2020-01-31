#include "FileArrayReader.h"
#include <fstream>
#include "gtest/gtest.h"
#include <iostream>
#include <algorithm>

TEST(FileBlockReaderTEST, Read) {
	std::vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	std::vector<int> v2{ 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
	std::vector<int> v3{ 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 };
	std::ifstream file(std::string(RESOURCES_DIRECTORY) + std::string("/array1.txt"));
	
	ASSERT_TRUE(file.is_open());
		
	FileArrayReader f(std::move(file));
	std::vector<int> buff;
	f.next(buff, 15);
	ASSERT_EQ(buff, v1);
	buff.clear();
	f.next(buff, 15);
	ASSERT_EQ(buff, v2);
	buff.clear();
	f.next(buff, 15);
	ASSERT_EQ(buff, v3);

}


TEST(TOP10FromFile, TOP10) {

	std::ifstream file(std::string(RESOURCES_DIRECTORY) + std::string("/array2.txt"));
	ASSERT_TRUE(file.is_open());
	FileArrayReader f(std::move(file));
	std::vector<int> buff;
	f.next(buff, 1000000);
	std::sort(buff.begin(), buff.end(), std::greater<int>{});
	std::cout << buff[0];
}
  

