#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <set>
#include <utility>

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
    std::cout << "hset and hget" << std::endl;
    redis.flushall();

    //四种写法
    redis.hset("key", "f1", "111");
    
    redis.hset("key", std::make_pair("f2","222"));

    //hset能够一次性插入多个field-value对
    redis.hset("key",{
        std::make_pair("f3", "333"),
        std::make_pair("f4", "444")
    });

    vector<std::pair<string, string>> fields = {
        std::make_pair("f5", "555"),
        std::make_pair("f6", "666")
    };
    redis.hset("key", fields.begin(), fields.end());

    auto result = redis.hget("key","f1");
    if(result){
        std::cout << "result : " << result.value() << std::endl;
    }else{
        std::cout << "result none" << std::endl;
    }
}

void test2(Redis &redis)
{
    std::cout << "hexits" << std::endl;
    redis.flushall();

    redis.hset("key", "f1", "111");
    redis.hset("key", "f2", "112");
    redis.hset("key", "f3", "113");

    bool result = redis.hexists("key","f1");
    std::cout << "result : " << result << std::endl;
}

void test3(Redis &redis)
{
    std::cout << "hdel" << std::endl;
    redis.flushall();

    redis.hset("key", "f1", "111");
    redis.hset("key", "f2", "112");
    redis.hset("key", "f3", "113");

    long long result = redis.hdel("key", "f1");
    std::cout << "result : " << result << std::endl;

    result = redis.hdel("key", {"f2","f3"});
    std::cout << "result : " << result << std::endl;
    
    long long len = redis.hlen("key");
    std::cout << "len : " << len << std::endl;

}

void test4(Redis &redis)
{
    std::cout << "hkeys and hvals " << std::endl;
    redis.flushall();

    redis.hset("key", "f1", "111");
    redis.hset("key", "f2", "112");
    redis.hset("key", "f3", "113");
    
    vector<string> fields;
    auto itfield = std::back_inserter(fields);
    redis.hkeys("key", itfield);

    PrintContainer(fields);

    vector<string> values;
    auto itvalue = std::back_inserter(values);
    redis.hvals("key", itvalue);

    PrintContainer(values);
}

void test5(Redis &redis)
{
    std::cout << "hmget and hmset" << std::endl;
    redis.flushall();

    redis.hmset("key",{
        std::make_pair("f1","111"),
        std::make_pair("f2","112"),
        std::make_pair("f3","113")
    });

    vector<std::pair<string,string>> pairs = {
        std::make_pair("f4","114"),
        std::make_pair("f5","115"),
        std::make_pair("f6","116"),
    };
    redis.hmset("key", pairs.begin(), pairs.end());


    vector<string> values;
    auto it = std::back_inserter(values);
    redis.hmget("key", {"f1","f2","f5","f6"}, it);

    PrintContainer(values);
}

int main()
{
    Redis redis("tcp://127.0.0.1:6379");

    //test1(redis);//hset,hget

    //test2(redis);//hexits

    //test3(redis);//hdel,hlen

    //test4(redis);//hkeys, hvals

    test5(redis);//hmget,hmset

    return 0;
}