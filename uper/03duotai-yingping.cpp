#include<iostream>
#include<string>
using namespace std;


class yingping
{
public:
    virtual void zhushui() = 0;
    virtual void chongpao() = 0;
    virtual void daoru() = 0;
    virtual void jiaru() = 0;

    void make()
    {
        zhushui();
        chongpao();
        daoru();
        jiaru();
    }
};


class coffee : public yingping
{
public:
    void zhushui()
    {
        cout<<"��ˮ"<<endl;
    }

    void chongpao()
    {
        cout<<"���ݿ���"<<endl;
    }

    void daoru()
    {
        cout<<"���뱭��"<<endl;
    }

    void jiaru()
    {
        cout<<"�����Ǻ�ţ��"<<endl;
    }
};


class tea : public yingping
{
public:
    void zhushui()
    {
        cout<<"��ˮ"<<endl;
    }

    void chongpao()
    {
        cout<<"���ݲ�Ҷ"<<endl;
    }

    void daoru()
    {
        cout<<"���뱭��"<<endl;
    }

    void jiaru()
    {
        cout<<"��������"<<endl;
    }
};

void dowork(yingping * y)
{
    y->make();
    delete y;
}


/*
int main()
{
    dowork(new coffee);

    cout<<"---------------------"<<endl;

    dowork(new tea);

}*/