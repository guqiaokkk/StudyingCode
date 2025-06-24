#include <iostream>
#include "contacts.pb.h"

int main(){
    std::string people_str;
    //对一个联系人的信息使用PB进行序列化，并将结果打印出来
    {
        contacts::PeopelInfo people;
        people.set_name("czy");
        people.set_age(14);
        if(!people.SerializeToString(&people_str))
        {
            std::cerr << "序列化联系人失败！ " << std::endl;
            return -1;
        }    
        std::cout << "序列化成功，结果是: " << people_str << std::endl; 
    }

    //对序列化后的内容用PB进行反序列化，解析出联系人信息并打印出来
    {
        contacts::PeopelInfo people;
        if(!people.ParseFromString(people_str)){
            std::cerr << "反序列化联系人失败！" << std::endl;
            return -1;
        }
        std::cout << "反序列化成功 !" << std::endl
                  << "name : " << people.name() << std::endl
                  << "age : " << people.age() << std::endl;
    }

    return 0;
}