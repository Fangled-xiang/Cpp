#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

/*
分治算法：规模为n的原问题无法直接求解，划分成多个子问题来求解。对子问题可以一直递归直到能求出解，再合并成原问题的解。
子问题之间相互独立(不独立考虑动态规划)，原问题的最优解也是子问题的最优解。
*/
/*二分收缩算法*/
#if 0
bool binarySearch(vector<int> vec, int i ,int j,int val)
{
    if(i>j)
    {
        return false;//找不到的递归结束条件
    }
    int mid = (i+j)/2;
    if(vec[mid] == val)
    {
        return true;
    }
    else if(vec[mid] > val)
    {
        return binarySearch(vec,i, mid-1,val);
    }
    else 
    {
        return binarySearch(vec, mid+1,j,val);
    }
}
int main()
{
    vector<int> vec;
    for(int i=0;i<11;i++)
    {
        vec.push_back(rand()%100);
    }

    sort(vec.begin(),vec.end());

    for(int v:vec)
    {
        cout<< v <<" ";
    }
    cout<<endl;

    bool result = binarySearch(vec, 0 ,vec.size()-1,34);
    cout << result<<endl;
}
#endif

/*
快排算法
*/
#if 0
int partation(int arr[],int l,int r)
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

void quicksort(int arr[0] ,int begin ,int end)
{
    if(begin >= end)
    {
        return;
    }
    int pos = partation(arr,begin,end);
    quicksort(arr,begin,pos-1);
    quicksort(arr,pos+1,end);

}

int main()
{
    int arr[11];
    for(int i=0;i<11;i++)
    {
        arr[i] = rand()%100;
        cout<< arr[i] << " ";
    }
    cout<<endl;

    quicksort(arr,0,10);

    for(int i=0;i<11;i++)
    {
        cout<< arr[i] << " ";
    }
    cout<<endl;

}
#endif

/*
利用快排来求topK（小）
l = k 时，就意味着找到了，前面的比自己小，后面比自己大（不用排序），速度非常快趋于0（n）
归并算法：对分治思想最好的体现
*/
#if 0
int partation(int arr[],int l,int r)
{
    int val = arr[l];//基准数//优化1：三数（l-r-middle）取中来作为基准先放到左边

    while (l<r)
    {
        while (arr[r] < val && l<r)//先找右边小于基准数的数，移到左边
        {
            r--;
        }

        if(l<r)
        {
            arr[l] = arr[r];
            l++;
        }


        while (arr[l] > val && l<r)//再找左边的边大于基准数的数，移到右边
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
void TopK(int arr[],int begin,int end ,int k)
{
    int pos = partation(arr,begin,end);
    if(pos+1 == k)
    {
        return;
    }
    else if (pos+1 < k)
    {
        TopK(arr,pos+1,end,k);
    }
    else
    {
        TopK(arr,begin,pos-1, k);
    }
}

int main()
{
    int arr[11];
    for(int i=0;i<11;i++)
    {
        arr[i] = rand()%100;
        cout<< arr[i] << " ";
    }
    cout<<endl;

    for(int k = 1;k<=11;k++)
    {
        TopK(arr,0,10,k);

        for(int i=0;i<k;i++)
        {
            cout<< arr[i] << " ";
        }
        cout<<endl;
    }

}
#endif

/*
合并个k个有序链表：归并的思想
*/
#if 0
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int(x))
        : val(x)
        ,next(nullptr)
    {}
};

ListNode*init_link(initializer_list<int> list)
{
    ListNode*head = nullptr;
    ListNode*p = nullptr;
    for(int v:list)
    {
        if(head == nullptr)
        {
            head = new ListNode(v);
            p = head;
        }
        else
        {
            p->next = new ListNode(v);
            p = p->next;
        }
    }
    return head;
    
}
ListNode*mergeTwoLink(ListNode*p1,ListNode*p2)
{   
    ListNode *head = nullptr;
    if(p1 == nullptr)
    {
        return p2;
    }
    if(p2 == nullptr)
    {
        return p1;
    }

    if(p1->val > p2->val)
    {
        head = p2;
        p2 = p2->next;
    }
    else
    {
        head = p1;
        p1 = p1->next;
    }

    ListNode*p = head;
    while (p1!= nullptr && p2 != nullptr)
    {
        if(p1->val > p2->val)
        {
            p->next = p2;
            p = p2;
            p2 = p2->next;
        }
        else
        {
            p->next = p1;
            p = p1;
            p1 = p1->next;
        }
    }

    if(p1!= nullptr)
    {
        p->next = p1;
    }
    if(p2 != nullptr)
    {
        p->next = p2;
    }
    return head;
    
}

ListNode*mergeLink(vector<ListNode*> &vlink,int i,int j)
{
    if(i>=j)
    {
        return vlink[i];
    }

    int mid = (i+j)/2;
    ListNode *left = mergeLink(vlink,i,mid);
    ListNode *right = mergeLink(vlink,mid+1,j);
    return mergeTwoLink(left,right);
}

int main()
{
    ListNode*p1 = init_link({1,3,5,7});
    ListNode*p2 = init_link({1,2,4,6,8});
    ListNode*p3 = init_link({5,6,7});
    ListNode*p4 = init_link({11,12,24,36,48});
    ListNode*p5 = init_link({21,23,25,57});
    vector<ListNode*> vlink;
    vlink.push_back(p1);
    vlink.push_back(p2);
    vlink.push_back(p3);
    vlink.push_back(p4);
    vlink.push_back(p5);

    ListNode * p = mergeLink(vlink,0,vlink.size()-1);
    for(ListNode*c = p1;c!=nullptr;c=c->next)
    {
        cout<<c->val<<" ";
    }
    cout<<endl;
}
#endif

/*
在对数时间O(log2(n)):内求中位数：
对数时间：二分搜索或者二叉树
两个升序数组m和n个，求加起来的元素中的中位数，时间要求对数时间内
*/