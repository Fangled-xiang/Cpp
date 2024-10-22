#include<iostream>
#include<list>
#include<string>

using namespace std;


//List 对自定义类型数据的排序案例，年龄升序、身高降序
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


//指定排序规则
bool comparestudent(student &p1, student &p2)
{
    if(p1.age_ == p2.age_)
    {
        return p1.height_ > p2.height_;
    }
    return p1.age_ < p2.age_;
}


int main()
{   
    list<student> l;

    student s1("fang", 18,188);
    student s2("xiang", 20,179);
    student s3("liu", 19,188);
    student s4("wen", 18,170);
    student s5("jin", 20,178);
    student s6("hao", 18,175);


    l.push_back(s1);
    l.push_back(s2);
    l.push_back(s3);
    l.push_back(s4);
    l.push_back(s5);
    l.push_back(s6);

    l.sort(comparestudent);

    for(list<student>::iterator it=l.begin();it!=l.end();it++)
    {
        cout<<(*it).name_<<"--"<<(*it).age_<<"--"<<(*it).height_<<endl;
    }


}