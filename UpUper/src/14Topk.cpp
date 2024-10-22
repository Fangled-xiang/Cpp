#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<functional>
#include<string>
#include<queue>//队列\优先级队列（默认是大根堆）
#include<unordered_map>//哈希表
using namespace std;


//大小根堆，需要一个大根堆（求小值），取前k个构成大根堆，依次把后面的数据放到堆顶，大于堆顶直接淘汰，小于堆顶就留下然后调整
//快排分割求topk，只需要在一边做快排分割，直到左边是k个，排序是两边做

int Partation1111(int arr[],int l,int r)//注意函数名别和前面重复了
{
    int val = arr[l];

    while (l<r)
    {
        while (arr[r] > val && l<r)
        {
            r--;
        }

        if(l<r)
        {
            arr[l] = arr[r];
            l++;
        }


        while (arr[l] < val && l<r)
        {
            l++;
        }

        if(l<r)
        {
            arr[r] = arr[l];
            r--;
        }   
    }
    
    arr[l] = val;
    return l;
}

void SelectTopk(int arr[],int begin , int end ,int k)
{
    int pos = Partation1111(arr,begin,end);
    if(pos == k-1)
    {
        return;
    }
    else if (pos > k-1)
    {
        SelectTopk(arr,begin,pos-1,k);
    }
    else
    {
        SelectTopk(arr,pos+1,end,k);
    }
}


// int main()
// {
//     int arr[] = {64,45,52,80,66,68,0,2,18,75};
//     int size = sizeof arr/sizeof arr[0];
//     int k = 3;
//     SelectTopk(arr, 0, size-1 ,k);
//     for(int i =0;i<k;i++)
//     {
//         cout<<arr[i]<<" ";
//     }
//     cout<<endl;



    // vector<int> vec;
    // srand(time(NULL));
    // for(int i = 0;i<1000;i++)
    // {
    //     vec.push_back(rand()%10000);
    // }

    
    // //求最小前五
    // priority_queue<int> maxheap;//大根堆
    // int k = 5;
    // for(int i=0;i<5;i++)
    // {
    //     maxheap.push(vec[i]); 
    // }
    // for(int i=5;i<vec.size();i++)
    // {
    //     if(maxheap.top()>vec[i])
    //     {
    //         maxheap.pop();
    //         maxheap.push(vec[i]);  //插入完自动调整
    //     }
    // }

    // while (!maxheap.empty())
    // {
    //     cout<<maxheap.top()<<" ";
    //     maxheap.pop();
    // }
    // cout<<endl;


#if 0
    //求最大前五
    priority_queue<int,vector<int>, greater<int>> minheap;//大根堆
    int k = 5;
    for(int i=0;i<5;i++)
    {
        minheap.push(vec[i]); 
    }
    for(int i=5;i<vec.size();i++)
    {
        if(minheap.top()<vec[i])
        {
            minheap.pop();
            minheap.push(vec[i]);  //插入完自动调整
        }
    }

    while (!minheap.empty())
    {
        cout<<minheap.top()<<" ";
        minheap.pop();
    }
    cout<<endl;


    //统计重复次数最小的前3个--哈希表查重加大根堆
    unordered_map<int ,int> map;
    for(auto key :vec)
    {
        map[key]++; //简略写法
    }

    //放入大根堆需要放入key-val 键值对代表重复次数
    using Type = pair<int,int>;
    using Comp = function<bool(Type&, Type&)>;  //调整的规则函数
    priority_queue<Type, vector<Type>, Comp> maxheap( [](Type& a ,Type& b)->bool{ return a.second < b.second; });

    auto it = map.begin();
    for(int i =0;i<3;i++,++it)
    {
        maxheap.push(*it);
    }

    for(;it!=map.end();++it)
    {
        if(maxheap.top().second > it->second)
        {
            maxheap.pop();
            maxheap.push(*it);
        }
    }

    while (!maxheap.empty())
    {
        cout <<"key: "<<maxheap.top().first<<" cnt: "<<maxheap.top().second<<endl;
        maxheap.pop();
    }
#endif

// }