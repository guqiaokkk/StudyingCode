#include <gtest/gtest.h>
#include <iostream>

int Add(int num1, int num2)
{
    return num1 + num2;
}

TEST(test, addtest)
{
    ASSERT_EQ(Add(10,20), 30);
    ASSERT_LT(Add(20,20), 50);
}
TEST(test, strtest)
{
    std::string str = "HELLO";
    EXPECT_EQ(str, "hello");
    printf("断言失败打印\n");
    EXPECT_EQ(str, "HELLO");
}


int main(int argc, char *argv[])
{
    //单元测试框架的初始化
    testing::InitGoogleTest(&argc, argv);
    //开始所有的单元测试
    return RUN_ALL_TESTS();
}