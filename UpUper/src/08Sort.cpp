#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
using namespace std;

//时间复杂度：冒泡排序效率最低(稳定)，选择排序次之(不稳定)，插入排序最高，希尔排序最高,希尔排序也不稳定
//趋于有序时插入最高，包括基础和高级排序算法
//稳定性；在原始数据相同大小的值，相对位置不改变则是稳定的，否则不稳定
//空间复杂性:都是O（1），不占用新的空间

//冒泡排序
void BubbleSort(int arr[], int size)
{
    bool flag = false;
    for(int i =0;i<size;i++)
    {
        for (int j = 0; j < size -1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = true;
            }
            
        }
        if(!flag)
        {
            return;
        }
        size --;
    }
}

//选择排序
void ChoiceSort(int arr[], int size)
{
    for(int i =0;i<size;i++)
    {
        int min = arr[i];
        int k = i;
        for(int j = i+1;j<size;j++)
        {
            if(min > arr[j])
            {
                min = arr[j];
                k = j;
            }
        }

        if(k != i)
        {
            int temp = arr[i];
            arr[i] = arr[k];
            arr[k] = temp;
        }
    }
}

//插入排序
void InsertSort(int arr[], int size) 
{
    for(int i = 1;i<size;i++)
    {
        int k = i;
        for(int j = i-1;j>=0;j--)
        {
            if(arr[j]>arr[k])
            {
                int temp = arr[j];
                arr[j] = arr[k];
                arr[k] = temp;
                k--;
            }
            else
            {
                break;
            }
        }
    }
}


//希尔排序：对插入排序进行优化，进行分组(使数据更加有序)再插入排序
void ShellSort(int arr[], int size) 
{
    for(int gap = size/2;gap>0;gap/=2)
    {
        for(int i = gap;i<size;i++)
        {
            int k = i;
            for(int j = i-gap;j>=0;j-=gap)
            {
                if(arr[j]>arr[k])
                {
                    int temp = arr[j];
                    arr[j] = arr[k];
                    arr[k] = temp;
                    k-=gap;
                }
                else
                {
                    break;
                }
            }
        }
    }
}


//快速排序
//选择一个基准数，小于的调到左边，大于的调到右边，然后对两边再次重复查找，直到有序
//递归实现
int Partation(int arr[],int l,int r)//快排分割函数
{
    int val = arr[l];//基准数//优化1：三数（l-r-middle）取中来作为基准先放到左边

    while (l<r)
    {
        while (arr[r] > val && l<r)//先找右边小于基准数的数，移到左边
        {
            r--;
        }

        if(l<r)
        {
            arr[l] = arr[r];
            l++;
        }


        while (arr[l] < val && l<r)//再找左边的边大于基准数的数，移到右边
        {
            l++;
        }

        if(l<r)
        {
            arr[r] = arr[l];
            r--;
        }   
    }
    
    arr[l] = val;//此时l==r
    return l;
}
//快排的递归接口
void QuickSort(int arr[], int begin ,int end)  //个数不一样没关系，直接重载了
{
    if(begin >= end) //快排递归结束条件
    {
        return;
    }

    // if(end - begin <= 50)//优化2：在相对有序后采用插排
    // {
    //     InsertSort(arr, begin,end);
    //     return;
    // }

    //在begin到end之间做一次快排处理
    int pos = Partation(arr, begin,end);//返回基准数放置位置，放在前面就好
    //左右分别快排：
    QuickSort(arr,begin,pos-1);
    QuickSort(arr,pos+1,end);
}
void QuickSort(int arr[], int size) 
{
    return QuickSort(arr, 0 ,size-1);
}


//归并排序：先递（不断地从中间截成两段，直到一个的时候递到头了），然后在归的过程中进行数据合并，达到排序的效果（需要申请额外的空间）
void Merge(int arr[],int l,int m,int r)
{
    int *p = new int[r-l+1];//申请额外内存空间
    int idx=0;
    int i = l;
    int j = m+1;
    while (i<=m && j<=r)
    {
        if(arr[i] <= arr[j])
        {
            p[idx] = arr[i];
            idx ++;
            i++;
        }
        else
        {
            p[idx] = arr[j];
            idx ++;
            j++;
        }
    }

    while (j<= r)
    {
            p[idx] = arr[j];
            idx ++;
            j++;
    }

    while (i<= m)
    {
            p[idx] = arr[i];
            idx ++;
            i++;
    }

    //拷贝到l->r区间内
    for(i=l,j=0;i<=r;i++,j++)
    {
        arr[i] = p[j];
    }
    delete[]p;//释放堆内存
}
void MergeSort(int arr[],int begin,int end)
{
    if(begin >= end)
    {
        return;
    }

    int mid = (begin+end)/2;
    //先递
    MergeSort(arr,begin,mid);
    MergeSort(arr,mid+1,end);
    //再归
    Merge(arr,begin,mid,end);

}
void MergeSort(int arr[],int size)
{
    return MergeSort(arr,0 ,size-1);
}




//基数排序（桶排序）：根据个位放到0-9十个桶中的一个，在按顺序拷贝到一起，在根据十位分桶再拷贝
//先找最长数字的位数，确定要处理的位数
//整数、负数、浮点数，都不太方便，排序是稳定的，相对位置不改变

void RadixSort(int arr[] , int size)
{
    int maxData = arr[0];
    for(int i = 1;i<size;i++)
    {
        if(maxData < arr[i])
        {
            maxData = arr[i];
        }
    }
    int len = to_string(maxData).size();

    vector<vector<int>> vecs;//实现桶结构，有点像二维数组，但是不是每维一样长；
    int mod = 10;
    int dev = 1;

    for(int i =0;i<len;mod*=10,dev*=10,i++)
    {
        vecs.resize(10);
        for(int j = 0;j<size;j++)
        {
            int index = arr[j] % mod / dev;
            vecs[index].push_back(arr[j]); 
        }
        //依次遍历所有桶
        int idx = 0;
        for(auto vec:vecs)
        {
            for(int v :vec)
            {
                arr[idx++] = v;
            }
        }

        vecs.clear();
    }
}




// int main()
// {
//     int arr[40];
//     for (int i = 0; i < 40; i++)
//     {
//         arr[i] = rand()%100 +1;
//     }
//     for(int val : arr)
//     {
//         cout<< val <<" ";
//     }
//     cout << endl;


//     RadixSort(arr, 40);
//     for(int val : arr)
//     {
//         cout<< val <<" ";
//     }
//     cout << endl;
    
// }