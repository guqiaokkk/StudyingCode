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

//get和set
void test1(sw::redis::Redis &redis)
{
    std::cout << "get和set的使用" << std::endl;
    
    //清空一下数据库，避免之前的数据残留的干扰
    redis.flushall();

    //使用set设置key
    redis.set("key1", "111");
    redis.set("key2", "222");
    redis.set("key3", "333");

    //使用get获取到key对应的value 
    auto value1 = redis.get("key1");
    //optional 可以隐式转成bool类型，可以直接在if中判定，如果是无效元素，就是返回false
    if(value1){
        std::cout << "value1:" << value1.value() << std::endl;
    }

    auto value2 = redis.get("key2");
    if(value2){
        std::cout << "value2:" << value2.value()  << std::endl;
    }

    auto value3 = redis.get("key3");
    if(value3){
        std::cout << "value3:" << value3.value()  << std::endl;
    }

    auto value4 = redis.get("key4");
    if(value4){
        std::cout << "value4:" << value4.value()  << std::endl;
    }
}

void test2(sw::redis::Redis &redis)
{
    std::cout << "exists的使用" << std::endl;

    redis.flushall();

    redis.set("key1", "111");
    
    auto t = redis.exists("key1");
    std::cout << t << std::endl;

    t = redis.exists("key2");
    std::cout << t << std::endl;

    redis.set("key2", "222");
    t = redis.exists({"key1", "key2", "key3"});
    std::cout << t << std::endl;
}

void test3(sw::redis::Redis &redis)
{
    std::cout << "del的使用" << std::endl;

    redis.flushall();

    redis.set("key1", "111");
    redis.set("key2", "222");

    auto res = redis.del("key1");
    std::cout << res << std::endl;

    redis.set("key3", "223");
    res = redis.del({"key1", "key2", "key3"});
    std::cout << res << std::endl;

    res = redis.exists({"key1","key2", "key3"});
    std::cout << res << std::endl;

}

void test4(sw::redis::Redis &redis)
{
    std::cout << "keys" << std::endl;
    redis.flushall();

    redis.set("key1", "111");
    redis.set("key2", "112");
    redis.set("key3", "113");
    redis.set("key4", "114");
    redis.set("key5", "115");
    redis.set("key6", "116");

    //keys的第二个参数，是一个插入迭代器，我们需要先准备好一个保存结果的容器
    //接下来再创建一个插入迭代器指向容器的位置，就可以把keys获取到的结果，依次通过刚才的插入迭代器插入到容器的指定位置中了
    vector<string> result;
    auto it = std::back_inserter(result);//末尾迭代器，实际上是在进行push_back操作
    redis.keys("*", it);

    PrintContainer(result);
}

void test5(sw::redis::Redis &redis)
{
    using namespace std::chrono_literals;

    std::cout << "expire | ttl" << std::endl;
    redis.flushall();

    redis.set("key1", "100");
    redis.expire("key1", std::chrono::seconds(10));
    //10s => std::chrono::seconds(10)

    std::this_thread::sleep_for(3s);

    auto time = redis.ttl("key1");
    std::cout << time << std::endl;
}

void test6(sw::redis::Redis &redis)
{
    std::cout << "type" << std::endl;
    redis.flushall();

    redis.set("key1", "111");
    string result = redis.type("key1");
    std::cout << result << std::endl;

    redis.lpush("key2", "222");
    result = redis.type("key2");
    std::cout << result << std::endl;

    redis.hset("key3", "aaa", "111");
    result = redis.type("key3");
    std::cout << result << std::endl;

    redis.sadd("key4", "aaa");
    result = redis.type("key4");
    std::cout << result << std::endl;

    redis.zadd("key5", "lvbu", 99);
    result = redis.type("key5");
    std::cout << result << std::endl;   
}

int main()
{
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    
    //test1(redis);//get,set

    //test2(redis);//exists
    
    //test3(redis);//del

    //test4(redis);//keys

    //test5(redis);//expire,ttl

    //test6(redis);//type
    
    
    
    return 0;
}