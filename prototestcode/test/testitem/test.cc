#include <iostream>
#include <string>
#include "contacts.pb.h"  // 确保包含生成的头文件

int main() {
    // 创建一个 Contact 对象
    Contact people;
    people.set_name("张珊");
    people.set_age(20);
    people.set_email("zhangsan@example.com");
    people.add_phone("1234567890");

    // 序列化到字符串
    std::string people_str;
    if (!people.SerializeToString(&people_str)) {
        std::cerr << "Failed to serialize." << std::endl;
        return 1;
    }

    std::cout << "序列化后的 people_str: " << people_str.size() << std::endl;

    // 反序列化
    Contact people2;
    if (!people2.ParseFromString(people_str)) {
        std::cerr << "Failed to parse." << std::endl;
        return 1;
    }

    std::cout << "Parse age: " << people2.age() << std::endl;
    std::cout << "Parse name: " << people2.name() << std::endl;

    return 0;
}
