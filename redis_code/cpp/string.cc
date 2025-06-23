#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
#include <thread>

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
    std::cout << "set and get" << std::endl;
    redis.flushall();

    redis.set("key1", "111");
    auto value = redis.get("key1");//auto是sw::redis:: ptionalString，它相当于一个盒子，里面包了一个string，要得到这个string，得.value()
    if(value){
        std::cout << "key1: " << value.value() << std::endl;
    }

    redis.set("key1", "222");
    value = redis.get("key1");
    if(value){
        std::cout << "key1: " << value.value() << std::endl;
    }
}

void test2(Redis &redis)
{
    //设置过期时间
    std::cout << "set设置过期时间" << std::endl;
    redis.flushall();

    redis.set("key", "111", 10s);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    auto time = redis.ttl("key");
    std::cout << time << std::endl;
}

void test3(Redis &redis)
{
    std::cout << "set NX and XX" << std::endl;
    redis.flushall();

    //redis.set("key", "2323");

    //set的重载版本中，没有单独提供 NX和XX的版本，必须搭配过期时间来使用
    redis.set("key", "111", 0s, sw::redis::UpdateType::EXIST);//0s不能不写

    auto value = redis.get("key");
    if(value){
        std::cout << "value: " << value.value() << std::endl;
    }else{
        std::cout << "value not exists" << std::endl;
    }
}

void test4(Redis &redis)
{
    std::cout << "mset " << std::endl;

    redis.flushall();
    
    // 第一种写法，使用多个初始化列表描述多个键值对
    //redis.mset({std::make_pair("key1", "111"), std::make_pair("key2", "222")});

    //第二个写法，把多个键值对提前组织到容器中，以迭代器的形式告诉mset
    vector<std::pair<string, string>> keys = {
        {"key1", "111"},
        {"key2", "222"}
    };
    redis.mset(keys.begin(), keys.end());

    auto value = redis.get("key1");
    if(value){
        std::cout << "value : " << value.value() << std::endl;
    }
    else{
        std::cout << "value not exist" << std::endl;
    }
}

void test5(Redis &redis)
{
    std::cout << "mget " << std::endl;
    redis.flushall();

    vector<std::pair<string, string>> keys = {
        {"key1", "111"},
        {"key2", "222"}
    };
    redis.mset(keys.begin(), keys.end());

    vector<sw::redis::OptionalString> result;
    auto it = std::back_inserter(result);
    
    redis.mget({"key1", "key2"}, it);

    PrintContainerOptional(result);
}

void test6(Redis &redis)
{
    std::cout << "setrange and getrange" << std::endl;
    
    redis.flushall();

    redis.set("key", "abcdfghijklmn");

    string result = redis.getrange("key", 2, 5);
    std::cout << "result : " << result << std::endl;

    redis.setrange("key", 2, "xyz");

    auto value = redis.get("key");
    std::cout << "value : " << value.value() << std::endl;

}

void test7(Redis &redis)
{
    std::cout << "incr and decr" << std::endl;
    redis.flushall();

    redis.set("key", "100");

    long long result = redis.incr("key");
    std::cout << "result : "<< result << std::endl;
    
    auto value = redis.get("key");
    std::cout << "value : "<< value.value() << std::endl;

    result = redis.decr("key");
    std::cout << "result : "<< result << std::endl;

    value = redis.get("key");
    std::cout << "value : "<< value.value() << std::endl;

}


int main()
{
    Redis redis("tcp://127.0.0.1:6379");

    //test1(redis);//set,get
    
    //test2(redis);//set设置过期
    
    //test3(redis);//set的nx,xx
    
    //test4(redis);  //mset

    //test5(redis); // mget;
   
   //test6(redis); // setrange and getrange

   //test7(redis);//incr and decr 
    return 0;
}