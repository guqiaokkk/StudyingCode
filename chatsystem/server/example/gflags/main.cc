#include <gflags/gflags.h>
#include <iostream>

DEFINE_string(ip, "127.0.0.1", "服务器监听地址，默认127.0.0.1");
DEFINE_int32(port, 8080, "服务器监听端口，默认8080");
DEFINE_bool(debug_enable, true, "是否持久化存储，true/false");

int main(int argc, char *argv[])
{
    google::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << FLAGS_ip << std::endl;
    std::cout << FLAGS_port << std::endl;
    std::cout << FLAGS_debug_enable << std::endl;
}