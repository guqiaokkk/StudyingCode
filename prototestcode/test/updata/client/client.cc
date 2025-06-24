#include <iostream>
#include <fstream>
#include "contacts.pb.h" 
using namespace std; 
using namespace c_contacts;
using namespace google::protobuf;

void PrintfContacts(const Contacts& contacts) { 
    for (int i = 0; i < contacts.contacts_size(); ++i) { 
        const PeopleInfo& people = contacts.contacts(i);
        cout << "------------联系⼈" << i+1 << "------------" << endl;
        cout << "联系⼈姓名：" << people.name() << endl;
        cout << "联系⼈年龄：" << people.age() << endl;
        int j = 1;
        for (const PeopleInfo_Phone& phone : people.phone()) {
            cout << "联系⼈电话" << j++ << ": " << phone.number() << endl;
        }

        const Reflection* reflection = PeopleInfo::GetReflection();
        const UnknownFieldSet &set = reflection->GetUnknownFields(people);
        for(int j = 0; j < set.field_count(); j++){
            const UnknownField& unknow_flied = set.field(j);
            cout << "未知字段 "  << j+1 << ": "
                <<  " 编号"     << unknow_flied.number();
            switch(unknow_flied.type()){
                case UnknownField::Type::TYPE_VARINT:
                    cout << " 值: " << unknow_flied.varint() << endl;
                    break;
                case UnknownField::Type::TYPE_LENGTH_DELIMITED:
                    cout << " 值: " << unknow_flied.length_delimited() << endl;
                    break;
                //case......
            }
        }
    }
}





int main() {
    Contacts contacts;
    // 先读取已存在的 contacts
    fstream input("../contacts.bin", ios::in | ios::binary);
    if (!contacts.ParseFromIstream(&input)) {
        cerr << "Failed to parse contacts." << endl;
        input.close();
        return -1;
    }
    
    // 打印 contacts
    PrintfContacts(contacts);
    input.close();
    return 0;
}