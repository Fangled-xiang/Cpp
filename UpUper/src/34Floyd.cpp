#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

using unit = unsigned int;
const unit INF = INT16_MAX;

/*
Dijikstra算法适合于单源的，多源路径的算法--弗洛伊德算法，同时可以适用于负权边
    核心思想：动态规划思想（核心就四行代码）：遍历图的每一个点，判断每一个点对的距离是否会因为点的加入而发生改变
        状态转移方程：dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])
*/


int main()
{
    vector<vector<unit>> graph = 
    {
        {0,6,3,INF,INF,INF},   //A
        {6,0,2,5,INF,INF},  //B
        {3,2,0,3,4,INF},  //C
        {INF,5,3,0,2,3},   //D
        {INF,INF,4,2,0,5},   //E
        {INF,INF,INF,3,5,0},   //F
    };

    //依次将每一个顶点加入
    for(int k=0;k <graph.size();k++)
    {
        for(int i =0; i<graph.size();i++)
        {
            for(int j=0;j<graph.size();j++)
            {
                graph[i][j] = min(graph[i][j] , graph[i][k]+graph[k][j]);
            }
        } 
    }

    for(auto line:graph)
    {
        for(auto dis :line)
        {
            cout <<dis<< " ";
        }
        cout<<endl;
    }

}