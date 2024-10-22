/*
串操作：ABCDCAB主串、 ABD子串/模式串  在主串中搜索的过程也叫模式匹配
BF的朴素算法：比较暴力且简单:时间复杂度O（m*n）、所以用的少
KMP算法：BF算法对子串的形状没有分析，导致许多没必要的回退，KMP不做这种回退，从而提高效率
前2者是基础算法

倒排索引
字典树   后面2者适用于大数据的搜索引擎
*/
#include<iostream>
#include<string>
using namespace std;

int BF(string s,string t)
{
    int i =0;
    int j =0;
    while (i < s.size() && j < t.size())
    {
        if(s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i-j+1;
            j = 0;
        }
    }
    
    if(j == t.size())
    {
        return i-j;
    }
    else
    {
        return -1;
    }
}


// int main()
// {
//     string s = "ABCDCABDEFG";
//     string t = "ABD";

//     int pos = BF(s,t);
//     cout<< pos <<endl;

// }