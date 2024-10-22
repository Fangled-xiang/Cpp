#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

class myprint
{
public:
    void operator()(int val)
    {
        cout <<val <<" ";
    }
};

void myprint2(int val)
{
    cout <<val <<" ";
}

void test01(const vector<int> &v)
{
    for_each(v.begin(),v.end(),myprint());
    cout<<endl;
    for_each(v.begin(),v.end(),myprint2);  //函数/函数对象都可以
    cout<<endl;

}

class student
{
public:
    student(string name, int age,int h)
        :name_(name)
        ,age_(age)
        ,height_(h)
    {}

    bool operator==(const student &p)
    {
        if(name_ == p.name_ && age_ == p.age_ && height_ == p.height_)
        {
            return true;
        }

        return false;
    } 


    string name_;
    int age_;
    int height_;
};


void test02(vector<int> v)
{
    vector<int>::iterator it = find(v.begin(),v.end(), 5);

    if(it == v.end())
    {
        cout << "no find" <<endl;
    }
    else
    {
        cout<<" find "<<endl;
    }


    vector<student> l;
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

    
    vector<student>::iterator it2 = find(l.begin(),l.end(), s6);
    if(it2 == l.end())
    {
        cout << "no find" <<endl;
    }
    else
    {
        cout<<" find "<<endl;
    }

}


class myfind
{
public:
    bool operator()(int val)
    {
        return val < 5;
    }
};

void test03(vector<int> v)
{
    vector<int>::iterator it = find_if(v.begin(),v.end(), myfind());
    if(it == v.end())
    {
        cout << "no find" <<endl;
    }
    else
    {
        cout<<" find "<<endl;
    }

    sort(v.begin(), v.end() );
    cout<< binary_search(v.begin(),v.end(), 62)  <<endl;
}


void test05()
{
    vector<int> v1,v2;
    for(int i =0;i<5;i++)
    {
        v1.push_back(rand()%100);
    }
    for(auto v:v1)
    {
        cout<<v <<" ";
    }
    cout<<endl;

    for(int i =0;i<5;i++)
    {
        v2.push_back(rand()%100);
    }
    for(auto v:v2)
    {
        cout<<v <<" ";
    }
    cout<<endl;

    vector<int> v3;
    v3.resize(v1.size()+v2.size());

    merge(v1.begin(),v1.end(),v2.begin(),v2.end(),v3.begin());

    for(auto v:v3)
    {
        cout<<v <<" ";
    }
    cout<<endl;

    reverse(v3.begin(), v3.end());
    for(auto v:v3)
    {
        cout<<v <<" ";
    }
    cout<<endl;


}

int main()
{
    vector<int> v;

    for(int i =1;i<15;i++)
    {
        int j = rand()%100;
        v.push_back(j);
        cout << j << " ";
    }
    cout <<endl;

    // test01(v);  // 遍历
    // test02(v);   // 查找（内置、自定义类型、需要在自定义类内重载==号）
    test03(v);   //  find_if、二分查找

    // test05();  //merge`reverse
}