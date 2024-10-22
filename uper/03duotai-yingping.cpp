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
        cout<<"ÖóË®"<<endl;
    }

    void chongpao()
    {
        cout<<"³åÅÝ¿§·È"<<endl;
    }

    void daoru()
    {
        cout<<"µ¹Èë±­ÖÐ"<<endl;
    }

    void jiaru()
    {
        cout<<"¼ÓÈëÌÇºÍÅ£ÄÌ"<<endl;
    }
};


class tea : public yingping
{
public:
    void zhushui()
    {
        cout<<"ÖóË®"<<endl;
    }

    void chongpao()
    {
        cout<<"³åÅÝ²èÒ¶"<<endl;
    }

    void daoru()
    {
        cout<<"µ¹Èë±­ÖÐ"<<endl;
    }

    void jiaru()
    {
        cout<<"¼ÓÈëÄûÃÊ"<<endl;
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