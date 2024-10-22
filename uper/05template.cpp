#include<iostream>
#include<string>

using namespace std;



template<typename T>
void myswap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}



/*
int main()
{
    char a = 's';
    char b = 'k';
    myswap(a,b);

    cout<<"a: "<<a <<"  b: "<< b<<endl;

    system("pause");
}*/