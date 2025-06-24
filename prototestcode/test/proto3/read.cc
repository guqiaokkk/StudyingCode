#include <iostream>
#include <fstream>
#include "contacts.pb.h"

using namespace std;

void PrintContacts(contact2::Contacts &contacts)
{
    for(int i = 0; i < contacts.contacts_size(); i++)
    {
        cout << "-----------联系人" << i+1 << "-----------" << endl;
        const contact2::PeopleInfo &people = contacts.contacts(i);
        cout << "联系人姓名" << people.name() << endl;
        cout << "联系人年龄" << people.age() << endl;
        for(int j = 0; j < people.phone_size(); j++){
            const contact2::PeopleInfo_Phone &phone = people.phone(j);
            cout << "联系人电话" << j+1 << " : " << phone.number();
            //联系人电话1:1331111(type)
            cout << "   (" << phone.PhoneType_Name(phone.type()) << ")  " << endl;
        }
        if(people.has_data() && people.data().Is<contact2::Address>())//判断有没有为data设值,值是不是address
        {
            contact2::Address address;
            people.data().UnpackTo(&address);//将any->address，转换后的值放到address里
            if(!address.home_address().empty())
            {
                cout << "联系人家庭住址: " << address.home_address() << endl;
            }
            
            if(!address.work_address().empty())
            {
                cout << "联系人工作住址: " << address.work_address() << endl;
            }
        }

        // if(people.has_qq()){

        // }else if(people.has_vx()){

        // }
        switch(people.other_contact_case())
        {
            case contact2::PeopleInfo::OtherContactCase::kQq:
                cout << "联系人QQ: " << people.qq() << endl;
                break;
            case contact2::PeopleInfo::OtherContactCase::kVx:
                cout << "联系人VX: " << people.vx() << endl;
                break;
            default:
                break;
        }

        if(people.remark_size())
        {
            cout << "备注信息: " << endl;
            for(auto it = people.remark().cbegin(); it != people.remark().cend(); it++)
            {
                cout << "     " << it->first << ":" << it->second << endl;   
            }
        }
    }
}






int main()
{
    contact2::Contacts contacts;

    //读取本地已经存在的通讯录文件
    fstream input("contacts.bin", ios::in | ios::binary);//ios::in读取，ios::binary以二进制读取
   
    if(!contacts.ParseFromIstream(&input)){
        cerr << "parse error! " << endl;
        input.close();
        return -1;
    }

    //打印通讯录列表
    PrintContacts(contacts);
     

    return 0;
}