#include<iostream>
#include<string>

using namespace std;

void test01()
{
    string s1;

    const char *str = "hello";
    string s2(str);

    string s3(s2);  //拷贝构造

    string(5,'a'); 

    s1 = s2;  //=已经重载过了
}



void test02()
{
    string s1 = "fang";
    string s2 = "xiang";

    s1 += s2;
    cout<<s1<<endl;

    s1.append(s2, 0,3);  //从第1个开始的3个拼到尾部
    cout<<s1<<endl;

    const char * add = "giegie";
    s1.append(add, 3);
    cout<<s1<<endl;


    s2.insert(3, "jjjjj");
    s2.erase(3,2);
    cout<<s2<<endl;


}

void test03()
{
    string s1 = "fangxiang";

    int pos1 = s1.find("xia" , 0);  //从0开始找
    int pos2 = s1.find("xiang" , 0, 3);  //从0开始找，xiang中的前3个

    int pos3 = s1.rfind("xiang");  //rfind最后一次出现,其他参数同上

    cout<<pos3<<endl;


    s1.replace(3,2,"ni");  //从第三个开始的2个字符替换成"ni"
    cout<<s1<<endl;


    string s2 = "fangxiang";
    const char*s3 = "fanniiang";
    cout<< s1.compare(s2) <<endl; //0是相等，>0,<0都是不相等，且返回ascall码的比较值
    cout<< s1.compare(s3) <<endl;

}


void test04()
{
    string s1 = "fangxiang";

    char c = s1.at(3);
    cout << c <<endl;
    cout<< s1[3] <<endl;  //[]重载了

    s1[3] = 'j';
    s1.at(3) = 'j';
    cout << s1 <<endl;

    //获取子串：
    string s4;
    s4 = s1.substr(3,5);
    cout<<s4<<endl;
}




int main()
{
    test01(); //string类的构造函数
    test02(); //string的追加操作、插入删除
    test03();  //查找和替换、比较
    test04();  //单个字符读写、字串读取
}