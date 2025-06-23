#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <chrono>

#include <sw/redis++/redis++.h>
#include "util.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;
using sw::redis::Redis;
using namespace std::chrono_literals;
void test1(Redis &redis)
{    std::cout << "lpush and lrange" << std::endl;
    redis.flushall();

    //插入单个元素
    redis.lpush("key", "111");

    //插入一组元素，基于初始化列表
    redis.lpush("key", {"222", "333", "444"});

    //插入一组元素，基于迭代器
    vector<string> values = {"555", "666", "777"};
    redis.lpush("key", values.begin(), values.end());
    
    //使用lrange来获取元素
    vector<string> result;
    auto it = std::back_inserter(result);
    redis.lrange("key", 0, -1, it);

    PrintContainer(result);
}



int main()
{
    Redis redis("tcp://127.0.0.1:6379");

    test1(redis);//lpush,lrange
    return 0;
}
