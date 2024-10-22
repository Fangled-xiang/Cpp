//栈：先进后出,顺序栈依赖数组实现（c++容器适配器stack），链式栈依赖链表实现
//专业名词：栈顶top标识位置，栈底，入栈，出栈，栈空、栈满
#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;


class SeqStack
{
public:
    SeqStack(int size = 10)
        : mtop(0)
        , mcap(size)
        {
            mpStack = new int[mcap];
        }

    ~SeqStack()
    {
        delete[]mpStack;
        mpStack = nullptr;
    }


public://c++容器适配器stack，push、pop出栈、top、empty、size
    void push(int val)
    {
        if(mtop == mcap)
        {
            expand(mcap*2);
        }
        mpStack[mtop++] = val;
    }

    void pop()
    {
        if(mtop == 0)
        {
            throw"stack is empty";
        }
        mtop--;
    }

    int top()
    {
        if(mtop == 0)
        {
            throw"stack is empty";
        }
        return mpStack[mtop-1];
    }

    bool empty() const
    {
        return mtop == 0;
    }

    int size() const
    {
        return mtop;
    }

    private:
        void expand(int size)
        {
            int*p = new int(size);
            memcpy(p, mpStack,mtop*sizeof(int));
            delete[]mpStack;
            mpStack = p;
            mcap = size;
        }

    private:
        int* mpStack;
        int mtop;
        int mcap;
};


// int main()
// {
//     SeqStack s;
//     int arr[] = {11,22,45,78,96,50,4};

//     for(int val:arr)
//     {
//         s.push(val);
//     }

//     while (!s.empty())
//     {
//         cout<< s.top()<<" ";
//         s.pop();
//     }
//     // s.top();
// }
