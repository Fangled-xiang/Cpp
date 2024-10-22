#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
不带权值的最短路径： 广度优先遍历的思想，水波纹扩散类似,代码在前面
带权值：dijkstra迪杰斯特拉算法、单源最短路径算法（多源、类似于需要去多家店取外卖）--多源考虑Floyd算法
    算法思想：贪心算法的典型应用，指定顶点A到其他所有的顶点的最短路径都会求出来（看视频讲解很清楚）
        利用到了S、U连两个集合
        无法处理负权边

*/


using unit = unsigned int;
const unit INF = INT16_MAX;

/*
int Dijkstra(vector<vector<unit>> & graph, int start ,int end)
{
    const int N = graph.size();
    vector<unit> dis(graph.size(), 0);
    vector<bool> use(graph.size(),false);

    use[start] = true;
    for(int i=0;i<N;i++)
    {
        dis[i] = graph[start][i];
    }

    for(int i=1;i<N;i++)
    {
        int k =-1;
        int min = INF;
        for(int j=0;j<N;j++)
        {
            if(!use[j]  && min > dis[j])
            {
                min = dis[j];
                k = j;
            }
        }

        use[k] = true;
        dis[k] = min;

        for(int j=0;j<N;j++)
        {
            if(!use[j]  && min+graph[k][j] < dis[j])
            {
                dis[j] = min+graph[k][j];
            }
        }
    }

    return dis[end];

}
*/


int Dijkstra(vector<vector<unit>> & graph, int start ,int end)
{
    const int N = graph.size();
    vector<unit> dis(graph.size(), 0);
    vector<bool> use(graph.size(),false);

    priority_queue< pair<unit,int>, vector<pair<unit,int>>, greater<pair<unit, int>>  > que;   //vector就当是默认自定义类型非要这么些就行

    use[start] = true;
    for(int i=0;i<N;i++)
    {
        dis[i] = graph[start][i];
        if( i != start)
        {
            que.emplace(graph[start][i] , i);
        }
    }

    while(!que.empty()) 
    {
        auto pair = que.top();
        que.pop();

        int k =pair.second;
        int min = pair.first;  //一下子就能找到最小权值

        if(use[k])
        {
            continue;//用过的直接出堆就行了
        }
        use[k] = true;

        for(int j=0;j<N;j++)
        {
            if(!use[j]  && min+graph[k][j] < dis[j])
            {
                dis[j] = min+graph[k][j];
                que.emplace(dis[j] , j);  //只能将更新在插入小根堆，相同编号的可能会重复插入，但是权值会改变，因为小根堆没法遍历进行修改
            }
        }
    }
    return dis[end];
}



int main()
{
    vector<vector<unit>> graph = 
    {
        {0,6,3,INF,INF,INF},
        {6,0,2,5,INF,INF},
        {3,2,0,3,4,INF},
        {INF,5,3,0,2,3},
        {INF,INF,4,2,0,5},
        {INF,INF,INF,3,5,0},
    };

    int distance = Dijkstra(graph , 0 , 3);  //o(n^2) 优化、使用最小堆o(long2(n))

    cout<<distance<<endl;
}