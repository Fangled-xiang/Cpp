//经典五大算法：分治算法、回溯算法、贪心算法、动态规划算法、分支限界算法（代码长）

//回溯算法：
//解空间：所有解的可能取值构成的空间:子集树、排列树
//算法：在所有解的解空间中，按照深度优先搜索的策略，从根节点搜索解空间。搜索的时候一般添加剪枝，来避免无效收缩。
//效率较低，但是比较通用

#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;


#if 0
/*子集树代码*/
void func(int arr[], int i, int length,int x[])
{
    if(i == length)
    {
        for(int j=0;j<length;++j)
        {
            if(x[j] == 1)
            {
                cout<<arr[j]<<" ";
            }
        }
        cout << endl;
    }
    else
    {
        x[i] = 1;//选择i节点，
        func(arr,i+1,length,x);//遍历i节点的左孩子

        x[i] = 0;//不选择
        func(arr,i+1,length,x); //遍历i节点右孩子
    }
}

int main()
{
    int arr[]={1,2,3};
    int length = 3;
    int x[3] = {0};
    func(arr, 0, length, x);
}
#endif


#if 0
/*整数选择问题：给一组整数，让选择一组整数使得整数的和，和剩下的和的差值最小*/
int arr[] = {12,6,7,11,16,3,10};
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> x;
vector<int> bestx;
int mini;
int sum = 0;
int r = 0;//剩余的和

void func(int i)
{
    if(i == length) //访问到了子集树的一个叶子节点
    {
        //sum 
        int result = abs(sum - r);
        if(result < mini)
        {
            mini = result;
            bestx = x;
        }
    }
    else
    {
        sum += arr[i];
        r -= arr[i];
        x.push_back(arr[i]);
        func(i+1); //选择i节点

        sum -= arr[i]; 
        r += arr[i];
        x.pop_back();//回溯回退
        func(i+1);
    }
}

int main()
{
    for(int v:arr)
    {
        r += v;
    }
    mini = r;

    func(0);

    for(int v:bestx)
    {
        cout<< v <<" ";
    } 

    cout << endl;
    cout<<"mim: " << mini <<endl;

    return 0;
}
#endif


/*
子集树剪枝叶：
整数选择问题：给一组2n个整数，让选择一组n个整数，使得整数的和，和剩下的和的差最小
*/
#if 0
int arr[] = {12,6,7,11,16,3,8,4};
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> x;
vector<int> bestx;
int mini;
int sum = 0;
int r = 0;//剩余的和
int left_ = length;//未处理的个数

void func(int i)
{
    if(i == length) //访问到了子集树的一个叶子节点
    {
        //sum 
        int result = abs(sum - r);
        if(result < mini)
        {
            mini = result;
            bestx = x;
        }
    }
    else
    {
        left_--; //表示处理了一个节点

        if(x.size()<length/2)  //剪左树枝，满了就不选了
        {
        sum += arr[i];
        r -= arr[i];
        x.push_back(arr[i]);
        func(i+1); //选择i节点
        sum -= arr[i]; 
        r += arr[i];
        x.pop_back();//回溯回退
        }

        //右树枝剪枝，已选+未来能选的不够n个，就剪掉
        if(x.size() + left_ >= length/2)
        {
        func(i+1);
        }

        left_ ++;
    }
}

int main()
{
    for(int v:arr)
    {
        r += v;
    }
    mini = r;

    func(0);

    for(int v:bestx)
    {
        cout<< v <<" ";
    } 

    cout << endl;
    cout<<"mim: " << mini <<endl;

    return 0;
}
#endif


/*
挑选数字：有一组树，挑选一组数字，使得和为指定值，存在打印，不存在也打印
*/
#if 0
int arr[] = {4,8,12,16,7,9,3,2};
const int length = sizeof(arr)/sizeof(arr[0]);
int number = 18;
vector<int> x;
int sum = 0;

void func1(int i)
{
    if(i == length)
    {
        if(sum != number)
        {
            return;
        }
        for(int v:x)
        {
            cout<< v<<" ";
        }
        cout <<endl;
    }
    else
    {
        if(sum + arr[i] <= number)
        {
        x.push_back(arr[i]);
        sum += arr[i];
        func1(i+1);
        x.pop_back();
        sum -= arr[i];
        }

        func1(i+1);
    }
}

void func2(int i,int number)  //类似于穷举:穷举法
{
    if(number == 0)
    {
        for(int v: x)
        {
            cout << v<< " ";
        }
        cout << endl;
    }
    else
    {
        for(int k = i;k<length;++k)
        {
            if(number >= arr[k])
            {
            x.push_back(arr[k]);
            func2(k, number-arr[k]);  //运行重复选择元素
            // func2(k+1, number-arr[k]);
            x.pop_back();
            }
        }
    }
}

int main()
{
    // func1(0);
    func2(0,number);
    return 0;
}
#endif

/*
0-1背包问题：有一组物品，起重量分别是w1，w2，wn，其价值分别是v1-vn，现在一个背包容量是c，怎么价值最大化
*/
#if 0
int w[] = {12,5,8,9,6};
int v[] = {9,11,4,7,8};
const int length = sizeof(w)/sizeof(w[0]);
vector<int> x;
vector<int> bestx;
int value;
int bestValue = 0;
int c = 20;
int weight = 0;

void func(int i)
{
    if(i == length)
    {
        if(value > bestValue)
        {
            bestValue = value;
            bestx = x;
        }
    }
    else
    {
        if(weight + w[i] <= c)
        {
            x.push_back(w[i]);
            value += v[i];
            weight += w[i];
            func(i+1);
            x.pop_back();
            value -= v[i];
            weight -= w[i];
        }
        
        func(i+1);

    }

}

int main()
{
    func(0);

    for(int v:bestx)
    {
        cout << v <<" ";
    }
    cout<<endl;
    cout<<"bestvalue: " << bestValue<<endl;

    return 0;
}
#endif

/*
解空间：排列树n个数，有n！个排列方式 ,用于求全排列                                                                                                                                                                                                                                                        
*/
#if 0
void swap(int arr[],int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void func(int arr[], int i,int length)
{
    if(i == length)
    {
        for(int j=0;j<length;j++)
        {
            cout<< arr[j] << " ";
        }
        cout <<endl;

    }
    else
    {
        for(int k = i;k<length;k++)
        {
            swap(arr,i,k);
            func(arr,i+1,length);
            swap(arr,i,k);
        }
    }
}

int main()
{
    int arr[] = {1,2,3,4};
    int length = sizeof(arr) / sizeof(arr[0]);
    func(arr,0,length);
}
#endif

/*
八皇后问题：八行八列，八个皇后不能处在同一行同一列同一条斜线
*/
#if 0
void swap(int arr[],int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
bool judge(int arr[], int i) //i表示当前皇后棋子的位置，即第i行，arr[i]列
{
    for(int j=0;j<i;j++)
    {
        if(i == j || arr[i] == arr[j] || abs(i - j) == abs(arr[i] - arr[j]))
        {
            return false;
        }
    }
    return true;
}
void func(int arr[],int i,int length)
{
    if(i == length)
    {
        for(int j =0;j<length;j++)
        {
            cout << arr[j] <<" ";
        }
        cout <<endl;

    }
    else
    {
        for(int k = i; k<length;k++)
        {
            swap(arr,i,k);
            if(judge(arr,i))
            {
                func(arr,i+1,length);
            }
            swap(arr,i,k);
        }

    }
}
int main()
{
    //把arr数组的下标当作行，下表对于元素值当作列
    int arr[] = {1,2,3,4,5,6,7,8};
    
    int n = 8;
    func(arr,0,n);

    return 0;
}
#endif

// /*枚举方法求解全排列:符合常规思想*/
// int arr[] = {1,2,3};
// const int N = 3;
// int state[N] = {0};
// vector<int> vec;

// void func(int i)
// {
//     if(i == N)
//     {
//         for(int v:vec)
//         {
//             cout<<v<<" ";
//         }
//         cout<<endl;
//     }
//     else
//     {
//         for(int k =0;k<N;k++)
//         {
//             if(state[k] == 0)
//             {
//                 state[k] = 1;
//                 vec.push_back(arr[k]);
//                 func(i+1);
//                 vec.pop_back();
//                 state[k] = 0;
//             }
//         }
//     }
// }

// int main()
// {

//     func(0);

//     return 0;
// }




