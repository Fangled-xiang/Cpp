/*
串操作：ABCDCAB主串、 ABD子串/模式串  在主串中搜索的过程也叫模式匹配
KMP算法：BF算法对子串的形状没有分析，导致许多没必要的回退，KMP不做这种回退，从而提高效率
核心思想：字符匹配失配后，不回退，只回退j且不一定回退到0
    在任意一个字符都可能回退，kmp算法需要给子串的每一个字符存储一个next数组，存储回退j的位置，也就是前面字符串的公共前后缀
时间复杂度接近于O（n）+ O（m）求了next数组，空间复杂度O（m）
*/
#include<iostream>
#include<string>
#include<memory>
using namespace std;

int *getNext(string str)
{
    int* next = new int[str.size()];
    int j =0;
    int k =-1;  //公共前后缀长度
    next[j] = k;

    while (j<str.size()-1)
    {
        if(-1 == k || str[k] == str[j])
        {
            j++;
            k++;
            next[j+1] = k;
        }
        else
        {
            k = next[k];//做回退，继续找
        }
    }

    return next;
}

/*
int KMP(string s,string t)
{
    int i =0;
    int j =0;

    int *next = getNext(t);
    unique_ptr<int> ptr(next);

    int size1 = s.size();//t.size()是无符号类型的，不能与有符号的进行比较
    int size2 = t.size();
    while (i < size1 && j < size2)
    {
        if((-1 == j) || s[i] == t[j])  //-1时首字母都匹配失败
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
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


int main()
{
    string s = "ABCDCABDEFG";
    string t = "ABD";

    int pos = KMP(s,t);
    cout<< pos <<endl;

}
*/