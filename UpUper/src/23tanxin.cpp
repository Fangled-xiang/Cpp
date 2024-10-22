#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

/*
贪心算法：没有固定的代码模板，只考虑当前子问题，不从整体考虑，局部最优，希望得到全局最优
*/


/*
硬币问题：1，3，5分，总值11，最少需要硬币
*/
#if 0
int main()
{
    int arr[]={1,3,5};
    int len = sizeof(arr)/sizeof(arr[0]);
    int c =11;

    sort(arr, arr+len, [](int a,int b)->bool{return a>b;}); //降序排序

    int idx = 0;
    int cnt = 0;
    while (c>0)
    {
        if(c>=arr[idx])
        {
            c -= arr[idx];
            cnt++;
        }
        else
        {
            idx ++;
        }
    }

    cout << cnt <<endl;

}
#endif

/*
m个柜台提供服务，每个柜台给一个用户提供服务的时间是t，问怎么排列，给所有用户提供的服务时间最快
*/
/*
struct Conter
{
    int id;
    int time;
};

int main()
{
    int arr[] = {3,2,4};
    const int m = sizeof(arr) / sizeof(arr[0]);
    int n = 15;
    sort(arr, arr+m, [](int a,int b)->bool{return a<b;}); //升序排序，优先快的排人

    Conter cons[m];
    for(int i =0;i<m;i++)
    {
        cons[i].id = arr[i];
        cons[i].time = arr[i];
    }


    int mintime = 0;
    int x[m] = {0};//安排人的数量

    for(int i =0;i<n;i++)
    {
        int time = cons[0].time * (x[0] + 1);

        int j = 1;
        for(;j<m;j++)
        {
            int t = cons[j].time * (x[j] + 1);
            if(t <= time)
            {
                x[j] ++;
                if(t > mintime)
                {
                    mintime = t;
                }
                break;
            } 
        }

        if(j == m)
        {
            x[0]++;
            mintime = time;
        }
    }

    cout <<mintime<<endl;
    for(int i=0;i<m;i++)
    {
        cout<<"id: " <<cons[i].id<<" num: " << x[i];
        cout << endl;
    }
    
    
    
}
*/
