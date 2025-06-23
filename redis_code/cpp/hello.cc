#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include <sw/redis++/redis++.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;


int main()
{
    //在创建 Redis对象的时候，需要在构造函数中， 指定redis服务器的地址和端口
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    //调用ping方法，让客户端给服务器发了一个ping，然后服务器就会返回一个pong，就通过返回值获取到
    string result = redis.ping();
    std::cout << result << std::endl;
    return 0;
}