#include <iostream>
#include <fstream>
#include "contacts.pb.h"
using namespace std;
using namespace s_contacts;



void AddPeopleInfo(PeopleInfo *people_info_ptr) {
    cout << "-------------新增联系⼈-------------" << endl;
    cout << "请输⼊联系⼈姓名: ";
    string name;
    getline(cin, name);
    people_info_ptr->set_name(name);

    // cout << "请输⼊联系⼈年龄: ";
    // int age;
    // cin >> age;
    // people_info_ptr->set_age(age);
    // cin.ignore(256, '\n'); 

    cout << "请输⼊联系⼈生日: ";
    int birthday;
    cin >> birthday;
    people_info_ptr->set_birthday(birthday);
    cin.ignore(256, '\n'); 

    for(int i = 1; ; i++) {
        cout << "请输⼊联系⼈电话" << i << "(只输⼊回⻋完成电话新增): ";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        PeopleInfo_Phone* phone = people_info_ptr->add_phone();
        phone->set_number(number);
    }
    cout << "-----------添加联系⼈成功-----------" << endl;
}





int main() {

    Contacts contacts;    
    // 先读取已存在的 contacts
    fstream input("../contacts.bin", ios::in | ios::binary);
    if (!input) {
        cout << "contacts.bin not found. Creating a new file." << endl;
    } else if (!contacts.ParseFromIstream(&input)) {
        cerr << "Failed to parse contacts." << endl;
        input.close();
        return -1;
    }

    // 新增⼀个联系⼈ 
    AddPeopleInfo(contacts.add_contacts());

    // 向磁盘⽂件写⼊新的 contacts
    fstream output("../contacts.bin", ios::out | ios::trunc | ios::binary);
    if (!contacts.SerializeToOstream(&output)) {
        cerr << "Failed to write contacts." << endl;
        input.close();
        output.close();
        return -1;
    }

    input.close();
    output.close();
    return 0;
}