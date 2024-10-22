//队列，先进先出，后进后出，环形队列，依赖数组实现需要先实现环形，链式队列


#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;


class Queue
{
    public://构造函数
        Queue(int size = 10):cap_(size),front_(0),back_(0),size_ (0)
        {
            pQue = new int[cap_];
        }
        ~Queue()
        {
            delete[]pQue;
            pQue = nullptr;
        }

        public://成员方法
        void push(int val)
        {
            if((back_ + 1)%cap_ == front_)
            {
                expand(2*cap_);
            }
            pQue[back_] = val;
            back_ = (back_+1)%cap_;
            size_++;
        }

        void pop()
        {
            if(back_ == front_)
            {
                cout<<"empty";
                return;
            }
            front_ = (front_+1)/cap_;//不需要删除，但是数据没用到了
            size_--;
        }

        int front()  const
        {
            if(back_ == front_)
            {
                cout<<"empty";
                throw"stack is empty";
            }
            return pQue[front_];
        }

        int back() const
        {
            if(back_ == front_)
            {
                cout<<"empty";
                throw"stack is empty";
            }
            return pQue[(back_-1 +cap_)%cap_];
        }

        bool empty()  const
        {
            return back_ == front_;
        }

        int size() const
        {
            // int size = 0;//遍历的方法，时间复杂度是O（n）
            // for(int i =front_;i != back_;i = (i+1)%cap_)
            // {
            //     size++;
            // }
            return size_;
        }



    private://内部私密函数
        void expand(int size) //不能直接扩，直接拷贝要遍历
        {
            int *p = new int[size];
            int j = 0;
            for(int i =front_;i != back_;i = (i+1)%cap_)
            {
                p[j] = pQue[i];
                j++;
            }
            delete[]pQue;
            pQue = p;
            cap_ = size;
            front_ = 0;
            back_ = j;
        }

    private://成员变量
        int* pQue;
        int cap_;
        int front_;
        int back_;
        int size_;
};


// int main()
// {
//     Queue s;
//     int arr[] = {11,22,45,78,96,50,4,100,200,300,400,500,666};

//     for(int val:arr)
//     {
//         s.push(val);
//     }

//     cout<<s.size()<<endl;
//     cout<< s.front()<<endl;
//     cout<< s.back()<<endl;

// }