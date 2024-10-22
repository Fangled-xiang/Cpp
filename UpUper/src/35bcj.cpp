#include<iostream>
using namespace std;


/*
并查集：树形数据结构（不一定是二叉树（考虑效率问题），但只能有一个父节点），解决元素分组的问题，不相交集合的合并（若干元素合并到一个/多个集合）以及查询（是否在一个集合）（社交关系等）
    思想：用一个数组（存储对应编号的元素的父节点编号，初始化存自己编号）表示整个深林，树的根节点唯一表示了一个集合，通过根确定在那个集合
        合并的时候只需要将根节点合并（有同一个根，则在一个集合中）
*/


const int SIZE = 9;
int parent[SIZE];
int height_[SIZE];

int find(int x)  //返回根节点编号
{
    while(x != parent[x])
    {
        x = parent[x];
    }
    return x;
}

/*
优化一：  并查集路径压缩：查询操作时，将访问过的每一个点的父节点！！修改成树根，递归中才能实现
*/
int rfind(int x)  //返回根节点编号
{
    if(x == parent[x])
    {
        return x;
    }
    return parent[x] = rfind(parent[x]);
}



void merge(int x, int y)   //不在一个集合才需要合并
{
    x = find(x);
    y = find(y);
    if(x != y)
    {
        //优化二:加权优化，合并时进行使合并的树高度低一些  把层数高的作为根节点(和优化一一起用可能会有问题，rank值没更新)
        if(height_[x] <= height_[y])
        {
            if(height_[x] == height_[y])
            {
                height_[y] ++;
            }
            parent[x] = y;

        }
        else
        {
            parent[y] = x;
        }
        

    }
}

int main()
{
    for(int i=0;i<SIZE;i++)
    {
        parent[i] = i;
        height_[i] = 1;
    }

    int x,y;
    for(int i =0;i<6;i++)
    {
        cin >> x >> y;
        merge(x,y);
    }

    cout<< (find(2) == find(8)  ? "OK" : "NO" ) <<endl;

}