#include <iostream>
#include <fstream>
#include "contacts.pb.h"

using namespace std;

void AddPeopleInfo(contact2::PeopleInfo* people)
{
    cout << "----------新增联系人----------" << endl;
    
    cout << "请输入联系人姓名 :" ;
    string name;
    getline(cin, name);
    people->set_name(name);

    cout << "请输入联系人年龄 :" ;
    int age;
    cin >> age;
    people->set_age(age);

    cin.ignore(256,'\n');//清除输入缓冲区的内容, 遇到 '\'就停止清除(包括'\'), 256表示最多清除到256个，若还没遇到'\'，也停止 

    for(int i = 0; ; i++)
    {
        cout << "请输入联系人电话" << i+1  << " (只输入回车完成联系人新增)";
        string number;
        getline(cin, number);
        if(number.empty())
        {
            break;
        }
        
        contact2::PeopleInfo_Phone* phone = people->add_phone();// people->add_phone()返回新增处的空间
        phone->set_number(number);

        cout << "请输入电话类型 ( 1.移动电话  2.固定电话 ): ";
        int type;
        cin >> type;
        cin.ignore(256,'\n');
        switch(type)
        {
            case 1:
                phone->set_type(contact2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_MP);
                break;
            case 2:
                phone->set_type(contact2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_TEL);
                break;    
            default:
                cout <<  "选择有误" << endl;
                break;
        }
    }
    contact2::Address address;
    cout << "请输入联系人家庭地址: ";
    string home_address;
    getline(cin, home_address);
    address.set_home_address(home_address);

    cout << "请输入联系人工作地址: ";
    string work_address;
    getline(cin, work_address);
    address.set_work_address(work_address);

    //Address -> Any
    people->mutable_data()->PackFrom(address);//mutable_data()拿到一块any的空间，再调用packfrom，将address->any

    cout << "请选择要添加的其他的联系方式 (1.qq   2.vx):";
    int other_contact;
    cin >> other_contact;
    cin.ignore(256,'\n');

    switch(other_contact)
    {
        case 1:{
            cout << "请输入联系人QQ号: ";
            string qqin;
            getline(cin, qqin);
            people->set_qq(qqin);
            break;
        }
        case 2:{
            cout << "请输入联系人VX号: ";
            string vxin;
            getline(cin, vxin);
            people->set_vx(vxin);
            break;
        }
        default:
            cout << "输入有误,未能设置联系方式" << endl;
            break;
    }
   
    for(int i = 0; ; i++){
        cout << "请输入备注" << i+1 << "标题(只输入回车完成备注新增): ";
        string remark_key;
        getline(cin, remark_key);
        if(remark_key.empty())
        {
            break;
        }

        cout << "请输入备注" << i+1 << "内容: ";
        string remark_value;
        getline(cin, remark_value);
        
        people->mutable_remark()->insert({remark_key, remark_value});
    }
   
    cout << "----------添加联系人成功----------" << endl;

}



int main()
{
    contact2::Contacts contacts;

    //读取本地已经存在的通讯录文件
    fstream input("contacts.bin", ios::in | ios::binary);//ios::in读取，ios::binary以二进制读取
    if(!input){
        cout << "contacts.bin not find, create new file!" << endl;
    }
    else if(!contacts.ParseFromIstream(&input)){
        cerr << "parse error! " << endl;
        input.close();
        return -1;
    }

    //向通讯录中添加一个联系人
    AddPeopleInfo(contacts.add_contacts());


    //将通讯录写入本地文件中
    fstream output("contacts.bin", ios::out | ios::trunc | ios::binary);//ios::out写入，ios::trunc覆盖写 
    if(!contacts.SerializeToOstream(&output))//做两件事，第一件事将内存中对象序列化，第二件事将序列化的结果放到output里
    {
        cerr << "write error!" << endl;
        input.close();
        output.close();
        return -1;
    }
    cout << "write success!" << endl;
    input.close();
    output.close();

    return 0;
}