#include "shared_ptr.h"
#include "gtest/gtest.h"
#include "test_shared_ptr.h"
#include <memory>

class TestShared {
public:
    explicit TestShared(std::string s, int q) :  str(std::move(s)), i(q) {
    }

    explicit TestShared(std::string &&s) : str(std::move(s)) {
    }

    int foo() {
        return 10;
    }
   std::string str;
    int i;
};


TEST(ShatedPtrTest, CreateShared) {
	my::shared_ptr<int> ptr(new int);
	*ptr = 10;
	ASSERT_EQ(*ptr, 10);
}

TEST(ShatedPtrTest, makeShared) {
	int i = 15412;
	std::string str("Hello, world!");
	my::shared_ptr<TestShared> ptr = my::make_shared<TestShared>(str, i);
	ASSERT_EQ(ptr->i, i);
	ASSERT_EQ(ptr->str, str);
}

TEST(ShatedPtrTest, TestTwoPointers) {
    int i = 15412;
    std::string str("Hello, world!");
    my::shared_ptr<TestShared> ptr1 = my::make_shared<TestShared>(str, i);
    {
        my::shared_ptr<TestShared> ptr2 = ptr1;
        ASSERT_EQ(ptr2.count(), 2);
        ASSERT_EQ(ptr1.count(), 2);
        ASSERT_EQ(ptr2->i, i);
        ASSERT_EQ(ptr2->str, str);
        
    }
    ASSERT_EQ(ptr1.count(), 1);
    ASSERT_EQ(ptr1->i, i);
    ASSERT_EQ(ptr1->str, str);
}


TEST(ShatedPtrTest, TestTwoPointers2) {
	std::vector<int> res{ 1, 2, 3, 4, 5, 6 };
	my::shared_ptr<std::vector<int>> ptr1 = my::make_shared<std::vector<int>>();
	ptr1->push_back(1);
	ptr1->push_back(2);
	ptr1->push_back(3);
	{
		my::shared_ptr<std::vector<int>> ptr2 = ptr1;
		ASSERT_EQ(ptr2.count(), 2);
		ASSERT_EQ(ptr1.count(), 2);
		ptr2->push_back(4);
		ptr2->push_back(5);
		ptr2->push_back(6);
	}
	ASSERT_EQ(ptr1.count(), 1);
	ASSERT_EQ(*ptr1, res);
}


TEST(ShatedPtrTest, TestBoolOperations) {
	int i = 15412;
	std::string str("Hello, world!");
	my::shared_ptr<TestShared> ptr1;;

	ASSERT_TRUE(ptr1.empty());
	ASSERT_TRUE(ptr1 == nullptr);
	ASSERT_TRUE(nullptr == ptr1);

	ASSERT_FALSE(ptr1 > nullptr);
	ASSERT_FALSE(nullptr < ptr1);

	ASSERT_TRUE(ptr1 >= nullptr);
	ASSERT_TRUE(nullptr <= ptr1);
}


TEST(ShatedPtrTest, TestMoveConstructor) {
	int i = 15412;
	std::string str("Hello, world!");
	my::shared_ptr<TestShared> ptr1 = my::make_shared<TestShared>(str, i);
	auto ptr2 = std::move(ptr1);
	ASSERT_TRUE(ptr1.empty());
	ASSERT_TRUE(ptr1 == nullptr);
	ASSERT_TRUE(nullptr == ptr1);

	ASSERT_FALSE(ptr1 > nullptr);
	ASSERT_FALSE(nullptr < ptr1);

	ASSERT_TRUE(ptr1 >= nullptr);
	ASSERT_TRUE(nullptr <= ptr1);
}

