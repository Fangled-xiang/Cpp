#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

/*
    动态规划算法（常用于求最优解）：与分治算法类似，也需要划分子问题（可能不独立，会重复求解），前一子问题的解为后一子问题的求解提供有用的信息。
    分治算法会有大量重复的子问题被求解，所以效率低
    子问题的解：状态（1），合并子问题的解：状态转移方程（2） dp[]数组 --二要素
*/


/*
硬币选择问题：有1，3，5分硬币，给定一个面值11，问最少所需数量
11：1+（10） 3+（8） 5+（6）
10：1+（9） 3+（6） 5+（4）
8：1+（7） ...
*/
#if 0
const int n =258;
int dp[n+1] = {0};

int func1(int n)
{
    if(dp[n] >0)
    {
        return dp[n];
    }

    if(n==1 || n==3 || n==5)
    {
        dp[n] = 1;  //代表一个子问题的最有解的性质
        return 1;
    }
    else if(n ==2 || n==4)
    {
        dp[n] = 2;
        return 2;
    }
    else
    {
        int count1 = func1(n-1) + 1;
        int count2 = func1(n-3) + 1;
        int count3 = func1(n-5) + 1;
        dp[n] =  min({count1,count2,count3});

        return dp[n];
    }
}
/*
    状态转移方程： dp[0] = 0;
                  dp[1] = 1 +dp[1-1] = 1
                  dp[2] = 1+dp[2-1] = 1+ 1 =2
                  dp[3] = 1+dp[3-1] = 2+1 =3;
                        = 1+dp[0] = 1;
                  dp[4] = ...
        推导得：dp[i] = min{1+dp[i-Vj]}
                  
*/
int func2(int c)
{
    int v[] = {1,3,5};
    int length = sizeof(v)/sizeof(v[0]);
    int *dp = new int[c+1]();
    for(int i =1;i<=c;i++)
    {
        dp[i] = i;
        for(int j =0;j<length;j++)
        {
            if(i>=v[j] && 1+ dp[i-v[j]] < dp[i])
            {
                dp[i] = 1+dp[i-v[j]];
            }
        }
    }
    return dp[c];
}

int main()
{
    // int num = func1(n); //递归实现
    int num = func2(n); //非递归实现！！
    cout << num << endl;
}
#endif


/*
斐波那契数列：前两个为1，后面为前两个数的和  
                func(5) --求func（4）、func（3）依次向下
*/
#if 0
const int n = 20;
int dp[n+1] ={0};
int fabnacci(int n)
{
    if(dp[n] > 0)
    {
        return dp[n];
    }

    if(n==1 || n==2 )
    {
        dp[n] = 1;
        return 1;
    }
    else
    {
        dp[n] = fabnacci(n-1) + fabnacci(n-2);
        return dp[n];
    }
}

int fabnacci2(int c)
{
    int *dp = new int[c+1]();
    dp[1] = dp[2] = 1;
    for(int i =3;i<=c;i++)
    {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[c];
}

int main()
{
    // int val = fabnacci(n);//递归
    int val = fabnacci2(n);//非递归
    cout << val <<endl;
    return 0;
}
#endif

/*
最大子段和：n个整数，可能为负，取其中一段连续的和最大值
-2，11，-4，13，-5，-2（若前面的字段和为负，使其和取0，就可以相当于没选前面的）
状态转移方程：
    dp[0] = val<0? 0: val
    dp[1] = arr[1] + dp[0];
    dp[2] = arr[2] + dp[1];
=>  dp[i] = arr[i] + dp[i-1]:以第i个元素为结尾的子段的和的值
*/
#if 0
int main()
{
    int arr[] ={-2,11,-4,13,-5,-2};
    vector<int> vec,vmax;
    const int n = sizeof(arr)/sizeof(arr[0]);
    int dp[n] = {0};
    dp[0] = arr[0] < 0? 0:arr[0];
    if(dp[0] > 0)
    {
        vec.push_back(arr[0]);
    }

    int maxval = dp[0];
    vmax = vec;

    for(int i = 1;i<n;i++)
    {
        dp[i] = arr[i] +dp[i-1];
        vec.push_back(arr[i]);
        if(dp[i]<0)
        {
            dp[i] = 0;
            while (!vec.empty())
            {
                vec.pop_back();
            }
            
        }
        if(dp[i] > maxval) 
        {
            maxval = dp[i];
            vmax = vec;
        }
    }

    cout << maxval<<endl;
    for(int v:vmax)
    {
        cout << v <<" ";
    }
    cout<<endl;
}
#endif


/*
求非降子序列的长度 5 3 4 1 8 7 9
双重for循环也可以求解，但是时间复杂度O（n^2） ，要求在0（n）也就是只有一个循环
dp[i] = arr[i] + dp[i-1]:以第i个元素为结尾的非降低子序列长度
*/
# if 0
int main()
{
    int arr[] ={5,3,4,6,1,8,7,9,11,15};
    const int n = sizeof(arr)/sizeof(arr[0]);
    int dp[n] = {0};
    dp[0] = 1;
    int maxlength = dp[0];

    for(int i = 1;i<n;i++)
    {
        if(arr[i] >= arr[i-1])
        {
            dp[i] = 1 +dp[i-1];
        }
        else 
        {
            dp[i] = 1;
        }
        if(dp[i] > maxlength)
        {
            maxlength = dp[i];
        }
    }
    cout << maxlength<<endl;

}
# endif

/*
LCS:求两个序列最长的公共子序列长度
helloworld
   hlweord  
==> 看末尾相不相等 ：相等包含进来，继续求helloworl与hlweor 
==> 不相等：情况（1）hellowor与hlweor、情况（2）helloworl与hlweo(不一定是连续的)
*/
#if 0
string str1 = "helloworld";
string str2 = "hlweord";
int **dp = nullptr;  //二维数组，dp[n][m] n表示第一个串的长度，m表示第二个串的长度，纪律的值就是LCS的长度

int LCS(string str1,string str2,int i,int j)  //分治算法求解
{
    if(i<0 || j<0)
    {
        return 0;
    }

    if(str1[i] == str2[j])
    {
        return LCS(str1,str2,i-1,j-1) + 1;
    }
    else
    {
        int len1 = LCS(str1,str2,i,j-1);
        int len2 = LCS(str1,str2,i-1,j);
        return max(len1,len2);
    }
}

int LCS2(string str1,string str2,int i,int j)
{
    if(dp[i][j]>= 0)
    {
        return dp[i][j];
    }

    if(i<0 || j<0)
    {
        return 0;
    }

    if(str1[i] == str2[j])
    {
        dp[i][j] =  LCS2(str1,str2,i-1,j-1) + 1;
    }
    else
    {
        int len1 = LCS2(str1,str2,i,j-1);
        int len2 = LCS2(str1,str2,i-1,j);
        if(len1 >= len2)
        {
            dp[i][j] = len1;
        }
        else
        {
            dp[i][j] = len1;
        }
    }
    return dp[i][j];
}

int main()
{
    // int len = LCS(str1,str2,str1.size()-1,str2.size()-1);//传入末尾下标,分治算法求解

    dp = new int*[str1.size()];
    for(int i = 0;i<str1.size();i++)
    {
        dp[i] = new int[str2.size()];
        for(int j=0;j<str2.size();j++)
        {
            dp[i][j] = -1;
        }
    }
    int len = LCS2(str1,str2,str1.size()-1,str2.size()-1);
    cout << len <<endl;
}
#endif


/*
0-1背包问题：不减枝，回溯算法是o（2^n）效率低，
这里用动态规划算法解决：w1-wn,v1-vn,容量c

动态规划解决问题的两个要素：
1.最优子结构
2.划分子问题非独立

状态：
dp(i,j):所选物品范围在i...i+1...n，背包容量是j，背包所容纳物品的最大值

状态转移方程：
i == n:
    wn>j,无法装入，dp(n，j) = 0
    wn<j,dp（n，j）= vn  //只有一个，肯定是考虑装的,物品值才能最大

i，i+1，...n
    wi>j,如法装入，dp（i，j） = dp（i+1，j）
    wi<j,第i个可以装，不装的话：dp（i，j）= dp（i+1，j） 装的话：d（i，j） = vi + dp(i+1,j-wi)


*/

# if 0
int w[] = {12,5,8,9,6};
int v[] = {9,11,4,7,8};
int c = 20;
const int n = sizeof(w)/sizeof(w[0]) -1 ;
int **dp = nullptr;

int bag(int i ,int j)
{
    if(dp[i][j]> 0)
    {
        return dp[i][j];
    }

    if(i == n)
    {
        if(w[i] > j)
        {
            return 0;
        }
        else
        {
            dp[n][j] = v[n];
        }
    }
    else
    {
        if(w[i] >j)
        {
            dp[i][j] = bag(i+1,j);
        }
        else
        {
            int val1 = bag(i+1,j);
            int val2 = v[i] + bag(i+1,j-w[i]);
            dp[i][j] = max(val1, val2); 
        }
    }
    return dp[i][j];
}

int main()
{

    dp = new int*[n+1];
    for(int i = 0;i<n+1;i++)
    {
        dp[i] = new int[c+1];
        for(int j =0;j<c+1;j++)
        {
            dp[i][j] = 0;
        }
    }

    int val = bag(0,c);
    cout << val <<endl;

    for(int i = 0;i<n+1;i++)
    {
        if(dp[i][c] != dp[i+1][c])
        {
            cout<< w[i] <<" ";
        }
    }
    cout<<endl;
}
#endif

/*
    给出一个三角形，找出指定向下的最小路径和，每一步只能移到到下一行相邻的节点
         2
        3 4
       6 5 7
      4 1 8 3
只使用O（n）的额外空间，n为总行数-----动态规划法
*/