#include<iostream>
#include<set>
#include<string>

using namespace std;

void printset(set<int> &s)
{
    for(set<int>::iterator it=s.begin(); it!=s.end();it++)
    {
        cout <<*it<<" ";
    }
    cout<<endl;
}

void printset(multiset<char> &s)
{
    for(multiset<char>::iterator it=s.begin(); it!=s.end();it++)
    {
        // putchar(*it);
        cout <<*it<<" ";
    }
    cout <<endl;
}


 
class MyConpare
{
public:
    bool operator() (int v1,int v2)
    {
        return v1 > v2;
    }
};



void test01()
{
    set<int> s;

    for(int i =1;i<15;i++)
    {
        s.insert(rand()%100);
    }

    printset(s);

    set<int,MyConpare> s1;

    for(int i =1;i<15;i++)
    {
        s1.insert(rand()%100);
    }

    for(set<int,MyConpare>::iterator it=s1.begin(); it!=s1.end();it++)
    {
        cout <<*it<<" ";
    }
    cout<<endl;


    
}

void test02()
{
    multiset<char> s1;
    s1.insert('g');
    s1.insert('b');
    s1.insert('b');
    s1.insert('y');

    printset(s1);

    set<int> s;
    pair<set<int>::iterator, bool> ret;
    ret = s.insert(1);

    ret = s.insert(1);

    if(! ret.second)
    {
        cout<<"fail..."<<endl;
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
    bool operator()(const student &s1,const student&s2)
    {
        if(s1.age_ == s2.age_)
        {
            return s1.height_  > s2.height_;
        }

        return s1.age_  < s2.age_;
    }
};

void test03()
{
    set<student,comparestu> l;

    student s1("fang", 18,188);
    student s2("xiang", 20,179);
    student s3("liu", 19,188);
    student s4("wen", 18,170);
    student s5("jin", 20,178);
    student s6("hao", 18,175);

    l.insert(s1);
    l.insert(s2);
    l.insert(s3);
    l.insert(s4);
    l.insert(s5);
    l.insert(s6);



    for(auto s : l)
    {
        cout<< s.name_ << "--" << s.age_ << "--" << s.height_<<endl;
    }

}

int main()
{
    test01();  //插入、设置从大到小（利用防函数）还是从小到大的排序
    test02(); //对组以及set与mulset的对比
    test03();  //自定义数据类型的排序
}