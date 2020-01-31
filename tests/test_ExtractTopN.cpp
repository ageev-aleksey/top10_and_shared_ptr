#include "IBlockBuffer.h"
#include <vector>
#include <memory>
#include "gtest/gtest.h"
#include <algorithm>

std::vector<int> ExtractTopN(std::shared_ptr<IBlockBuffer<std::vector<int>>> data, size_t N, size_t block_size);



class Buffer : public IBlockBuffer<std::vector<int>> {
public:
    Buffer(std::vector<int> buff) {
        buffer = std::move(buff);
        pos = 0;
    }


    virtual size_t next(std::vector<int> &buff_ptr, size_t block_read) override {
        if(buffer.size() > (pos+block_read)) {
			buff_ptr.resize(block_read);
			std::copy(buffer.begin()+pos, buffer.begin()+(pos+block_read), buff_ptr.begin());
		}
       else{
			block_read = std::distance((buffer.begin() + pos), buffer.end());
			buff_ptr.resize(block_read);
            std::copy(buffer.begin()+pos, buffer.end(), buff_ptr.begin());
			
        }
		pos += block_read;
		return block_read;
    }
private:
    std::vector<int> buffer;
    size_t pos;
};

TEST(BufferTest, Nextblock) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Buffer buff(v);
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};
    std::vector<int> v3 = {7, 8, 9};
    std::vector<int> v4 = {10};

    std::vector<int> copy;

    buff.next(copy, 3);
    ASSERT_EQ(copy, v1);
    copy.clear();
    buff.next(copy, 3);
    ASSERT_EQ(copy, v2);
    copy.clear();
    buff.next(copy, 3);
    ASSERT_EQ(copy, v3);
    copy.clear();
    buff.next(copy, 3);
    ASSERT_EQ(copy, v4);
}


TEST(TestExtract, ExtractTop3) {
	std::vector<int> d{ 1, 5, 8, 4, 0, 4, 7, 48, 14, 21, 47, 99, 100, 40, 0, 1, 50, };
	std::shared_ptr<IBlockBuffer<std::vector<int>>> ptr = std::make_shared<Buffer>(d);
	std::vector<int> res = ExtractTopN(ptr, 3, 5);
	std::sort(d.begin(), d.end(), std::greater<>{});
	std::sort(res.begin(), res.end(), std::greater<>{});
	ASSERT_EQ(res[0], d[0]);
	ASSERT_EQ(res[1], d[1]);
	ASSERT_EQ(res[2], d[2]);
}

TEST(TestExtract, ExtractTop5) {
	std::vector<int> d{ 1, 5, 8, 4, 0, 4, 7, 48, 14, 21, 47, 99, 100, 40, 0, 1, 50, };
	std::shared_ptr<IBlockBuffer<std::vector<int>>> ptr = std::make_shared<Buffer>(d);
	std::vector<int> res = ExtractTopN(ptr, 5, 5);
	std::sort(d.begin(), d.end(), std::greater<>{});
	std::sort(res.begin(), res.end(), std::greater<>{});
	for (size_t i = 0; i < 5; i++) {
		ASSERT_EQ(res[i], d[i]);
	}
}


TEST(TestExtract, ExtractTop10) {
	std::vector<int> d{ 1, 5, 8, 4, 0, 4, 7, 48, 14, 21, 47, 99, 100, 40, 0, 1, 50, 
						1, 5, 8, 4, 0, 4, 7, 48, 14, 21, 47, 99, 100, 40, 0, 1, 50, };
	std::shared_ptr<IBlockBuffer<std::vector<int>>> ptr = std::make_shared<Buffer>(d);
	std::vector<int> res = ExtractTopN(ptr, 10, 13);
	std::sort(d.begin(), d.end(), std::greater<>{});
	std::sort(res.begin(), res.end(), std::greater<>{});
	for (size_t i = 0; i < 5; i++) {
		ASSERT_EQ(res[i], d[i]);
	}
}