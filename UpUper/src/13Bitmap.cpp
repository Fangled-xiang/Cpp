#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<memory> //自动释放内存
#include<string>
using namespace std;

// 哈希表(适用于快速查重，内存充足，一亿=100M个，=100M*4 = 400M内存，哈希表*2 = 800M内存)
//位图算法（非常省内存）：适用于状态简单，数据量大，内存少的情况（将数字是否出现过存到一个位数数组里-通过/%查找映射 ）
//通过位操作来获取值（1还是0），和置1----------100000000一亿个数据/32+1 3.2M（省了好多内存，/32是因为int类型是32个字节）
//需要直到最大值是多少，按max/32+1 开辟int类型的数组、出现了几次不好求、适用最大值>=个数情况


//内存限制同时，需要快速查找，可以使用布隆过滤器
//由一个位数组+k个哈希函数组成：经过k个哈希函数计算，得到bitmap位数组里面的一组位的序号，并把相应的位置成1
//搜索元素：如果几位全是1，则key存在，如果有一个为0，则不存在（说数据在，但其实不一定存在！！！存在误判，说不在则一定不在--这是存在意义）
//可以进行搜索和增加，不能删除、哈希函数多则效率低，但误报率低
//应用：redis缓存、提示非法钓鱼网站  //实现略

// int main()
// {
//     vector<int> vec{12,78,90,12,78,123,8,9};
//     int max = vec[0];
//     for(int i =1;i<vec.size();i++)
//     {
//         if(vec[i] > max)
//             max = vec[i];
//     }

//     int* bitmap = new int[max/32 +1]();//()初始化为0
//     unique_ptr<int> ptr(bitmap);//自动释放内存

//     //找第一个重复出现的数字
//     for(auto key :vec)
//     {
//         int index = key/32;
//         int offset = key%32;

//         //取key对应位的值
//         if(0 == (bitmap[index] & (1<<offset)))
//         {
//             //没出现过
//             bitmap[index] |= (1<<offset);
//         }
//         else
//         {
//             cout<<"is: "<<key<<endl;
//             break;
//         }
//     }

// }