#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;


#include<fstream>
#include <sstream>

/*
并查集应用：最小生成树-克鲁斯卡尔算法的核心
    连通图：无向图中任意两点都相通（不一定是直接连接）
    强连通图：有向图中
    联通网：有权值
    生成树：是一个连通子图，包含全部的n个顶点，但是边只有n-1条（在添加一条就会成环）
    最小生成树：边的代价之和最小（现实意义：修路使得所有都连通且代价最小） --prim算法（加点法）、Kruskal算法（加变法，适合边多的）

算法思想：
    先将边按权值进行排序，依次选择，且边的两个顶点应属于两颗不同的树，合并成一棵树（n-1条边后就停止）
    一条边就类似前面并查集的一个关系
*/

struct Edge
{
    Edge(int s,int e,int c)
        :start(s)
        ,end(e)
        ,cost(c)
    {}
    int start;
    int end;
    int cost;
};

const int SIZE = 1000;
int parent[SIZE];


vector<Edge> readfile(const string filePath)
{
    vector<Edge> edgs;
    ifstream ifs;
    ifs.open(filePath.c_str(),ios::in);

    string line;
    int i =0;
    while (getline(ifs, line)) 
    {
        char c1 = line[0];
        int s=static_cast<int>(c1);

        c1 = line[2];
        int e=static_cast<int>(c1);

        c1 = line[4];
        int c = c1-'0';

        edgs.emplace_back(s,e,c);
    }
    ifs.close();
    return edgs;
}

int find(int x) 
{
    if(x == parent[x])
    {
        return x;
    }
    return parent[x] = find(parent[x]);
}



int main()
{
    for(int i=0;i<SIZE;i++)
    {
        parent[i] = i;
    }

    vector<Edge> edgs=readfile("E:\\VScode\\Code\\UPUPUP\\src\\36bian.txt");

    sort(edgs.begin(),edgs.end(), [](auto &a, auto &b) ->bool{return a.cost <b.cost;});

    for(auto e:edgs)
    {
        printf("%c -> %c cost:%d  \n", e.start,e.end, e.cost);
    }
    cout <<endl;

    for(int i =0;i<edgs.size();i++)
    {
        int a = find(edgs[i].start);
        int b = find(edgs[i].end);

        if(a != b)
        {
            parent[b] = a;
            printf("%c -> %c cost:%d  \n", edgs[i].start,edgs[i].end, edgs[i].cost);
        }
    }

}