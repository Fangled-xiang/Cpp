#include<iostream>
#include<stack>
#include<queue>

using namespace std;

void test01()
{
    stack<int> s;

    for(int i =1;i<15;i++)
    {
        s.push(rand()%100);
    }

    while (!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }

}

void test02()
{

    queue<int> q;

    for(int i =1;i<15;i++)
    {
        q.push(rand()%100);
    }

    while (!q.empty())
    {
        cout<<q.front()<<" " <<q.back()<<endl;
        q.pop();
    }

    
}

int main()
{
    test01();  //栈容器的操作、先进后出
    test02();  //队列容器的操作、先进先出
}