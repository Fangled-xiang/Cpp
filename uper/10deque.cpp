#include<iostream>
#include<deque>
#include<algorithm>

using namespace std;


//和vector基本一致

void test01()
{
    deque<int> deq1;

    for(int i =1;i<6;i++)
    {
        deq1.push_back(i);
    }


    deq1.insert(deq1.begin()+3, 9);

    // deq1.push_front(10);
    // deq1.push_front(10);
    // deq1.pop_front();     //多了一个头部删除


    for(auto i:deq1)
    {
        cout<< i <<" ";
    }
    cout <<endl;

}

void test02()
{
    
    deque<int> deq1;

    for(int i =1;i<15;i++)
    {
        deq1.push_back(rand()%100);
    }


    sort(deq1.begin(),  deq1.end());  //排序


    for(auto i:deq1)
    {
        cout<< i <<" ";
    }
    cout <<endl;
}

int main()
{
    test01(); //常规操作


    test02();  //排序


}