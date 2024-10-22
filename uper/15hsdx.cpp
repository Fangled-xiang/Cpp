#include<iostream>
#include<string>

using namespace std;


class myprint
{
public:
    myprint()
    {
        this->count = 0;
    }

    void operator()(const string &s)
    {
        cout<<s<<endl;
        count ++;
    }

    int count;
};



void test01()
{
    myprint p;

    p("hello");
    cout<<p.count<<endl;

    p("hello");
    cout<<p.count<<endl;

    p("hello");
    cout<<p.count<<endl;

}


int main()
{
    test01();
}