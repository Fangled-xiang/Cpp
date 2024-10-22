#include<iostream>
#include<string>
#include<list>
#include<queue>
#include<vector>
#include<fstream>
#include <sstream>
using namespace std;

/*
有向图：digraph，和树的区别：不需要一个根节点，且一个节点到另一个节点可以有好几条路径
        有向图：由顶点（节点）和有向弧（有向边）构成
        顶点的度：出度和入度：即有几个出或者进入的边，无向不区分
无向图：没有出向边和入项边的区分、且顶点不能自己到自己（有向可以）

存储结构：邻接矩阵/邻接表/十字链表/邻接多重表
    邻接矩阵：n个节点，n*n的矩阵，如果i节点连接指向了j，那i行j列元素为1/权值，否则为0，（横看出度、竖看入度）
            无向图则ji也为1/权值-对角对称且对角线上全是0
            如果是一个稀疏矩阵，存储效率（空间利用率）太低
    邻接表：n个数组（结构体数组），每个里面包含节点的数据以及一条链表（每个节点可以有权值、编号）、每条链表后面接着邻接于顶点的编号（邻接出去的编号）
        逆邻接表（链表存储入度的）
    十字链表：有向图既考虑出度，也考虑入度，复杂但存储效率和邻接表一样快
        顶点有两个指针域，一个指向出边表第一个节点、一个入边表 ，边表还是一个链表，但是每个节点有四个元素（有点复杂，看视频讲解，也不复杂，文字不好描述）
            每个节点都会有两条，代表两个信息（入和出）、入边遍历到不为空写入
    邻接多重表：考虑无向图冗余存储的问题
        顶点一样，边结点会有变化，包括了五个信息
        
    图的遍历：（类似于二叉树的遍历）
        深度优先遍历：优先走完一条，走到头就回退
        广度优先遍历：优先把一个节点的去向遍历一遍  （利用队列实现，出入队列）
*/


class Digraph
{
private:    
    struct Vertic  //顶点
    {
        Vertic(string data)
            :data_(data)
        {}
        string data_;
        list<int> adjList_;
    };

    vector<Vertic> vertics;
    

public:
    //从配置文件读入顶点和边的信息，生成邻接表
    void readFile(const string filePath)
	{
        ifstream ifs;
        ifs.open(filePath.c_str(),ios::in);

        vertics.emplace_back(" ");

        string line;
        while (getline(ifs, line)) 
        {
            vertics.emplace_back(line);
            getline(ifs, line);

            stringstream ss(line);
            string num;
            while (getline(ss, num, ',')) 
            {
                if(stoi(num) > 0)
                {
                    vertics.back().adjList_.emplace_back(stoi(num));
                }
            }
        }

        ifs.close();
	}

	// 输出邻接表信息
	void show() const
	{
		for (int i = 1; i < vertics.size(); i++)
		{
			cout << vertics[i].data_ << " : ";
			for (auto no : vertics[i].adjList_)
			{
				cout << no << " ";
			}
			cout << endl;
		}
		cout << endl;
	}


public:  //遍历
     void dfs()  //deep
     {
        vector<bool> vied(vertics.size(),false);
        dfs(1, vied);
        cout<<endl;
     }

     void bfs()  //Breadth
     {
        vector<bool> vied(vertics.size(),false);
        queue<int> que;

        que.push(1);
        while (!que.empty())
        {
            int cur = que.front();
            que.pop();
            cout << vertics[cur].data_ <<" ";
            vied[cur] = true;

            for(auto num :vertics[cur].adjList_)
            {
                if(!vied[num])
                {
                    que.push(num);
                    vied[num] = true;
                }
            }
        }
        cout<<endl;
        
     }

private:
    void dfs(int start ,vector<bool> &vied)
    {
        if(vied[start])
        {
            return;
        }
        cout <<vertics[start].data_ <<" ";
        vied[start] = true;

        //递归
        for(auto num:vertics[start] .adjList_)
        {
            dfs(num, vied);
        }
    }



public:
    void shortpath(int start, int end)
    {
        vector<bool> vied(vertics.size(),false);
        queue<int> que;

        vector<int> path(vertics.size(), 0);

        que.push(start);
        while (!que.empty())
        {
            int cur = que.front();
            if(cur == end)
            {
                break;
            }
            que.pop();

            vied[cur] = true;

            for(auto num :vertics[cur].adjList_)
            {
                if(!vied[num])
                {
                    que.push(num);
                    vied[num] = true;
                    path[num] = cur;
                }
            }
        }
        cout<<endl;

        if(que.empty())
        {
            cout<<"no  find"<<endl;
        }
        else
        {
            // while (end != 0)
            // {
            //     if(end == start)
            //     {
            //         cout<< vertics[end].data_<<endl;;
            //         return;
            //     }

            //     cout<< vertics[end].data_ <<" <== ";
            //     end = path[end];
            // }

            showPath(end, path); //正序打印，递归实现，归的时候打印就行
            
        }
    }
 private:
    void showPath(int end, vector<int>& path)
    {
        if(end == 0)  //start的来源是0，作为递归结束条件
        {
            return;
        }
        showPath(path[end], path);
        cout <<vertics[end].data_<< " ";
    }

};






int main()
{
    Digraph g;
    g.readFile("E:\\VScode\\Code\\UPUPUP\\src\\32data.txt");
    g.show();

    g.dfs();
    g.bfs();

    g.shortpath(1,9);

}