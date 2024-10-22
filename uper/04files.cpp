#include<iostream>
#include<string>
#include<fstream>

using namespace std;


void test0()
{
    ofstream ofs;
    ofs.open("E:\\VScode\\Code\\UPUPUP\\test.txt", ios::app);

    ofs <<"sahdah" <<endl;
    ofs<< "khdaj"<<endl;
    ofs<<"ahdsjhaj"<<endl;

    ofs.close();

}


void read()
{
    ifstream ifs;
    ifs.open("E:\\VScode\\Code\\UPUPUP\\test.txt", ios::in);
    string buf;
    while(getline(ifs, buf))
    { 
        cout << buf<<endl;
    };
}


/*
int main()
{

    read();



}
*/