#include<iostream>
#include<map>
#include<string>

using namespace std;

void test01()
{   
    map<int,int> m;

    for(int i=1;i<10;i++)
    {
        m.insert(pair<int,int>(rand()%100,rand()%10));
    }

    for(auto v : m)
    {
        cout << "key: "<<v.first <<"  val: "<<v.second<<endl;
    }
    

}

void test02()
{
    //insert
    map<int,string> m;

    m.insert(pair<int,string>(1,"10"));

    m.insert(make_pair(2,"22"));

    m[3] = "35";  //第四种如果不小心插入错误，不存在的val，会自动创建一个val
    
    for(auto v : m)
    {
        cout << "key: "<<v.first <<"  val: "<<v.second<<endl;
    }
}


class student
{
public:
    student(string name, int age, int height)
        : age_(age)
        ,name_(name)
        ,height_(height)
    {}
public:
    int age_;
    int height_;
    string name_;
};

class comparestu
{
public:
    bool operator()(const int p1, const int p2)
    {
        return p1 > p2;
    }
};

void test03()
{
    student s1("fang", 18,188);
    student s2("xiang", 20,179);
    student s3("liu", 19,188);
    student s4("wen", 18,170);
    student s5("jin", 20,178);
    student s6("hao", 18,175);

    map<int,student,comparestu> m;

    m.insert(pair<int,student>(1,s1));
    m.insert(make_pair(2, s2));
    m.insert(make_pair(3, s3));
    m.insert(make_pair(4, s4));
    m.insert(make_pair(5, s5));
    m.insert(make_pair(6, s6));

    for(auto s : m)
    {
        cout<<"key: "<<s.first<<"   "<< s.second.name_ << "--" << s.second.age_ << "--" << s.second.height_<<endl;
    }

}



int main()
{
    // test01();  //构造  pair对组
    // test02();  //插入、删除
    test03();  //设定排序规则
}