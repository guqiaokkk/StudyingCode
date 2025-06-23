#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include <sw/redis++/redis++.h>
#include "util.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;

using sw::redis::Redis;

void test1(Redis &redis)
{
    std::cout << "zadd and zrange" << std::endl;
    redis.flushall();

    redis.zadd("key","吕布", 99);

    redis.zadd("key",{
        std::make_pair("赵云",98),
        std::make_pair("里斯",97)
    });

    vector<std::pair<string,double>> members = {
        std::make_pair("我",100),
        std::make_pair("会议",92)
    };
    redis.zadd("key", members.begin(), members.end());

    //zrange 支持两种主要的风格
    //1.只查询member，不带score
    //2.查询member,同时带score
    //关键在于看插入迭代器指向的容器的类型
    //指向的容器只是包含一个string，就是只查询member
    //指向的容器包含的是一个pair，里面有string和double，就是查询member，同时带有分数
    
    vector<string> memberResults;
    auto itone = std::back_inserter(memberResults);
    redis.zrange("key", 0, -1, itone);
    PrintContainer(memberResults);

    vector<std::pair<string,double>> selects;
    auto ittwo = std::back_inserter(selects);
    redis.zrange("key", 0, -1, ittwo);
    PrintContainerPair(selects);
}

void test2(Redis &redis)
{
    std::cout << "zcard " << std::endl;
    redis.flushall();

    redis.zadd("key", "zhangsan", 92);
    redis.zadd("key", "lisi", 98);
    redis.zadd("key", "wangwu", 96);
    redis.zadd("key", "zhaoliu", 95);

    long long result = redis.zcard("key");
    std::cout << "result: " << result << std::endl;
}

void test3(Redis &redis)
{
    std::cout << "zrem " << std::endl;
    redis.flushall();

    redis.zadd("key", "zhangsan", 92);
    redis.zadd("key", "lisi", 98);
    redis.zadd("key", "wangwu", 96);
    redis.zadd("key", "zhaoliu", 95);

    redis.zrem("key", "lisi");

    long long result = redis.zcard("key");
    std::cout << "result: " << result << std::endl;
}

void test4(Redis &redis)
{
    std::cout << "zscore " << std::endl;
    redis.flushall();

    redis.zadd("key", "zhangsan", 92);
    redis.zadd("key", "lisi", 98);
    redis.zadd("key", "wangwu", 96);
    redis.zadd("key", "zhaoliu", 95);

    auto score = redis.zscore("key", "wangwu");
    if(score){
        std::cout << "score: " << score.value() << std::endl;
    }else{
        std::cout << "score wrong" << std::endl;
    }
}

void test5(Redis &redis)
{
    std::cout << "zrank" << std::endl;
    redis.flushall();

    redis.zadd("key", "zhangsan", 92);
    redis.zadd("key", "lisi", 98);
    redis.zadd("key", "wangwu", 96);
    redis.zadd("key", "zhaoliu", 95);

    auto rank = redis.zrank("key", "lisi");
    if(rank){
        std::cout << "rank : " << rank.value() << std::endl;
    }else{
        std::cout << "rank wrong" << std::endl;
    }
}


int main()
{
    Redis redis("tcp://127.0.0.1:6379");
    
    //test1(redis);//zadd,zrange
    
    //test2(redis);//zcard

    //test3(redis);//zrem

    //test4(redis);//zscore

    test5(redis);//zrank

    return 0;
}