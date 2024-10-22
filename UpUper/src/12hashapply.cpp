#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
using namespace std;

 //主要就是用于！！！查重！！！：哈希表(适用于快速查重，内存充足)、位图算法、布隆过滤器
void test01()
{   
    vector<int> vec;
    srand(time(NULL));
    for(int i = 0;i<10000;i++)
    {
        vec.push_back(rand()%10000);
    }

    //找第一个重复的数字
    unordered_set<int> s1; //不允许重复的哈希表，unordered_multiset
    for(auto key : vec)
    {
        auto it = s1.find(key);
        if(it == s1.end())
        {
            s1.insert(key);
        }
        else
        {
            cout << "key: "<<key<<endl;
            break;
        }
    }
}


void test02()
{
    vector<int> vec;
    srand(time(NULL));
    for(int i = 0;i<10000;i++)
    {
        vec.push_back(rand()%10000);
    }

    //查找重复出现的数字以及次数
    unordered_map<int ,int> m1;
    for(int key:vec)
    {
        auto it = m1.find(key); 
        if(it == m1.end())
        {
            m1.emplace(key,1);
        }
        else
        {
            it->second += 1;
        }
    }
    for(auto pair:m1)
    {
        if(pair.second > 1)
        {
            cout<<"key: "<<pair.first <<"count: "<<pair.second <<endl;
        }
    }
}


void test03()
{
    //找第一个没重复的字符
    string src ="jhfakjhfkjsfvwb";
    unordered_map<int ,int> m;
    for(char ch : src)
    {
        // auto it = m1.find(ch); 
        // if(it == m1.end())
        // {
        //     m1.emplace(ch,1);
        // }
        // else
        // {
        //     it->second += 1;
        // }
        m[ch]++;//等同于上面注释部分
    }

    for(char ch:src)
    {
        if(m[ch] == 1)
        {
            cout<<"is: "<<ch<<endl;
            return;
        }
    }

    cout<<"no"<<endl;
    return;
}

void test04()
{
    //查重相关问题：两个文件a，b，里面放了很多ip（url地址，email地址），让你找出两个重复的ip  
    //放a到一个哈希表，然后遍历b，在哈希表中搜索，搜到的即输出，0（1）的操作
}


// //哈希表应用
// int main()
// {
//     test03();
// }