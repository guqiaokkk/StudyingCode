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
{   
     std::cout << "lpush and lrange" << std::endl;
    redis.flushall();

    //插入单个元素
    redis.lpush("key", "111");

    //插入一组元素，基于初始化列表
    redis.lpush("key", {"222", "333", "444"});

    //插入一组元素，基于容器
    vector<string> values = {"555", "666", "777"};
    redis.lpush("key", values.begin(), values.end());
    
    //使用lrange来获取元素
    vector<string> result;
    auto it = std::back_inserter(result);
    redis.lrange("key", 0, -1, it);

    PrintContainer(result);
}

void test2(Redis &redis)
{
    std::cout << "rpush" << std::endl;

    redis.flushall();
    
    //插入单个元素
    redis.rpush("key", "111");

    //插入一组元素，基于初始化列表
    redis.lpush("key", {"222", "333", "444"});

    
    //插入一组元素，基于容器
    vector<string> values = {"555", "666", "777"};
    redis.rpush("key", values.begin(), values.end());

    //使用lrange来获取元素
    vector<string> result;
    auto it = std::back_inserter(result);
    redis.lrange("key", 0, -1, it);
    PrintContainer(result);
}

void test3(Redis &redis)
{
    std::cout << "lpop, rpop" << std::endl;
    redis.flushall();

    redis.lpush("key", {"1","2","3","4"});

    auto it = redis.lpop("key");
    if(it){
        std::cout << "lpop value :" << it.value() << std::endl;
    }

    it = redis.rpop("key");
    if(it){
        std::cout << "rpop value: "<< it.value() << std::endl;
    }
}
 
void test4(Redis &redis)
{
    using namespace std::chrono_literals;
    std::cout << "blpop and brpop" << std::endl;
    redis.flushall();

    auto result = redis.blpop({"key", "key1", "key2"},10s);
    if(result){
        std::cout << "key :" << result.value().first << std::endl;
        std::cout << "value :" << result.value().second << std::endl;
    }else{
        std::cout << "wrong result " << std::endl;
    }
}

void test5(Redis &redis)
{
    std::cout << "llen" << std::endl;
    redis.flushall();

    redis.lpush("key", {"111", "222", "3333"});
    
    long long len = redis.llen("key");
    std::cout << len << std::endl;
}


int main()
{
    Redis redis("tcp://127.0.0.1:6379");

    //test1(redis);//lpush,lrange
   
    //test2(redis);//rpush
    
    //test3(redis);//lpop,rpop
    
    //test4(redis);//blpop,brpop
    
    //test5(redis);//llen



    return 0;
}
