#include<DataStruct.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>

using namespace std;

class Array
{
    public:
        Array(int size = 10)
            :mCur(0)
            ,mCap_(size)//初始化
        {
            mpArr = new int[mCap_]();
        }

        ~Array()//释放
        {
            delete []mpArr;
            mpArr = nullptr;
        }

    public:
        void push_back(int val)//增加
        {
            if(mCur == mCap_)
            {
                expand(2*mCap_);
            }
            mpArr[mCur++] = val;
        }

        void pop_back()//尾部删除
        {
            if(mCur == 0)
            {
                return;
            }
            mCur--;
        }

        
        void insert(int pos, int val) //插入
        {
            if(pos <0 || pos >mCur)
            {
                return;
            }
            if(mCur == mCap_)
            {
                expand(2*mCap_);
            }

            for(int i = mCur-1;i>=pos;i--)
            {
                mpArr[i+1] = mpArr[i];
            }
            mpArr[pos] = val;
            mCur++;
            
        }


        void erase(int pos)//位置删除
        {
            if(pos <0 || pos >=mCur)
            {
                return;
            }
            for(int i = pos+1;i<mCur;i++)
            {
                mpArr[i-1] = mpArr[i];
            }
            mCur--;

        }


        int find(int val)//查找
        {
            for(int i = 0;i<mCur;i++)
            {
                if(mpArr[i] == val)
                {
                    return i;
                }
            } 
            return -1;
        }

        void show()const
        {
            for(int i = 0;i<mCur;i++)
            {
                cout<<mpArr[i]<<" ";
            }
            cout<<endl;
        }

    private:
        int* mpArr;
        int mCap_;//容量
        int mCur;//个数

        void expand(int size)//内部扩容接口
        {
            int*p  = new int[size];
            memcpy(p, mpArr, sizeof(int)*mCap_);
            delete[]mpArr;
            mpArr = p;
            mCap_ = size;
        }
};


void arr_test()
{
    Array arr;
    srand(time(0));
    for(int i =0 ;i <10;i++)
    {
        arr.push_back(rand()%100);
    }
    arr.show();
    
    arr.pop_back();
    arr.show();

    arr.insert(0,100);
    arr.show();

    int pos = arr.find(100);
    if (pos != -1)
    {
        arr.erase(pos);
        arr.show();
    }
        
}


//*********************************************************************** *///应用
//双指针应用
int randdata()
{
    int arr[10] = {0};
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand()%100;
    }
    for (int v : arr)
    {
        cout << v <<" ";
    }
    cout<<endl;
}
 
void reverse(char arr[],int size) 
{
    char*p = arr;
    char*q = arr+size-1;
    while (p<q)
    {
        char ch = *p;
        *p = *q;
        *q = ch;
        p++;
        q--;
    }
    
}

void adjustArr(int arr[], int size)//奇偶数调整,左偶右奇
{
    int*p = arr;
    int*q = arr+size-1;
    while (p<q)
    {
        if((*p & 0x1) == 0)
        {
            p++;
            continue;
        }

        if((*q & 0x1) == 1)
        {
            q--;
            continue;
        }
        int ch = *p;
        *p = *q;
        *q = ch;
        p++;
        q--;
    }
}

void test_adjustarr()
{
    int arr[10] = {0};
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand()%100;
    }
    for (int v : arr)
    {
        cout << v <<" ";
    }
    cout<<endl;

    adjustArr(arr, 10);
        for (int v : arr)
    {
        cout << v <<" ";
    }
    cout<<endl;

}