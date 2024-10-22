#include<iostream>
#include<string>
using namespace std;

class Abs_Caculator
{
public:
    int num1_;
    int num2_;

    virtual int get_result()
    {
        return 0;
    }
};

class add_caculator : public Abs_Caculator
{
public:
    int get_result()
    {
        return num1_ + num2_;
    }
};


class mul_caculator : public Abs_Caculator
{
public:
    int get_result()
    {
        return num1_ * num2_;
    }
};




int main()
{
Abs_Caculator * acb = new mul_caculator;
acb->num1_ = 10;
acb->num2_ = 5;
cout<<acb->get_result()<<endl;
}