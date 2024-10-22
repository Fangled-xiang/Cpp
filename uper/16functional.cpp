#include<iostream>
#include<string>
#include<vector>
#include<functional>
#include<algorithm>

using namespace std;

void test01()
{
    plus<int> p;

    cout<< p(10,25)<<endl;

    negate<int> n;

    cout<< n(9) <<endl;
}

void test02()
{
    vector<int> v;

    for(int i =1;i<15;i++)
    {
        v.push_back(rand()%100);
    }
    
    sort(v.begin(), v.end(),  greater<int>() ) ;    //内建,默认是less

}

void test03()
{


}

int main()
{
    test01();//算术仿函数
    test02();//关系仿函数
    test03();//逻辑仿函数
}