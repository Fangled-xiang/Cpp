#include<iostream>
using namespace std;
#include<string>
#include<algorithm>

class Person  //自定义数据类型
{
public:
    Person()
    {}

    Person(string name,int age,int height)
        :age_(age)
        ,name_(name)
        ,height_(height)
    {}
public:
    int age_;
    string name_;
    int height_;

};

Person p1("fang", 18,180);
Person p2("xiang",20,172);
Person p3("liu", 15,158);
Person p4("long", 22,175);
Person p5("wang",10,178);

class mycompare
{
public:
    bool operator()(const Person &p1,const Person&p2)
    {
        if(p1.age_ == p2.age_)
        {
            return p1.height_  > p2.height_;
        }
        return p1.age_  < p2.age_;
    }
};