#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <set>

#include <sw/redis++/redis++.h>
#include "util.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::set;
using std::unordered_map;
using sw::redis::Redis;

void test1(Redis &redis)
{
    std::cout << "zadd and zmembers" << std::endl;
    redis.flushall();

    //一次添加一个元素
    redis.sadd("key", "111");

    //一次添加多个元素（使用初始化列表）
    redis.sadd("key", {"222","333","444"});

    //一次添加多个元素（使用迭代器）
    set<string> elems = {"555", "666", "777"};
    redis.sadd("key",elems.begin(), elems.end());

    //获取到上述元素
    //此处用来保存smembers的结果，使用set更为合适
    set<string> result;

    //auto it = std::std::back_inserter(result)   给vector用
    //由于此处set里的元素顺序是固定的，指定一个result.end()或者result.begin()，或者其他位置的迭代器，都无所谓
    auto it = std::inserter(result, result.end());
    redis.smembers("key", it);
    
    PrintContainer(result);
}

void test2(Redis &redis)
{
    std::cout << "sismember " << std::endl;
    redis.flushall();

    redis.sadd("key", {"111", "222", "333"});

    bool result = redis.sismember("key", "222");
    std::cout << "result : " << result << std::endl;
}

void test3(Redis &redis)
{
    std::cout << "scard " << std::endl;
    redis.flushall();

    redis.sadd("key", {"111","222","333"});
    long long result = redis.scard("key");
    std::cout << "result :" << result << std::endl;
}

void test4(Redis &redis)
{
    std::cout << "spop" << std::endl;
    redis.flushall();

    redis.sadd("key",{"111","222","333"});
    auto result = redis.spop("key");
    if(result){
        std::cout << "result :" << result.value() << std::endl; 
    }else{
        std::cout << "result wrong" << std::endl; 
    } 
}

void test5(Redis &redis)
{
    std::cout << "sinter" << std::endl;//求交集
    redis.flushall();

    redis.sadd("key1", {"111", "222", "333"});
    redis.sadd("key2", {"111", "222", "444"});

    set<string> result;
    auto it = std::inserter(result, result.end());
    redis.sinter({"key1", "key2"}, it);

    PrintContainer(result);
}

void test6(Redis &redis)
{
    std::cout << "sinterstore" << std::endl;
    redis.flushall();

    redis.sadd("key1", {"111", "222", "333"});
    redis.sadd("key2", {"111", "222", "444"});

    long long len = redis.sinterstore("key3", {"key1", "key2"});
    std::cout << "len : " << len << std::endl;

    set<string> result;
    auto it = std::inserter(result, result.end());
    redis.smembers("key3", it);

    PrintContainer(result);
}

int main()
{
    Redis redis("tcp://127.0.0.1:6379");
    
    //test1(redis); //sadd,smembers

    //test2(redis);//sismember

    // test3(redis);//scard

    //test4(redis);//spop

    //test5(redis);//sinter

    test6(redis);//sinterstore
    
    return 0;
}