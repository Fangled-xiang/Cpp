#include<iostream>
#include<vector>
#include<list>
#include <algorithm>
using namespace std;

//线性探测哈希表时间复杂度增加，同时对于多进程的工作，就难以应对，同一个表中的数据就可能被其他进程覆盖（采用分段互斥锁，才能保证一定的并发量）
//关联容器：一般采用链式哈希表：除留余数法(散列函数/哈希函数)，每个桶进行链式头插，不再是放一个数据（有点像基数排序中用的）
//同样也会进行装载扩容
//优化：当一个桶内的链表长度大于10，把桶里的链表转化成红黑树，链式哈希表每个桶都可以上互斥锁，不同桶之间就可以进行并发进行，而不用分段；

class HashTable
{
private:
    vector<list<int>> table_; //链表加桶的数据结构
    int useBucketNum_; //使用桶的个数
    double loadFactor_; //哈希表装载因子，经验可取3/4

    int table_size;  //哈希表长度；
    static const int PRIME_size = 10;//素数表大小
    static int primes_[PRIME_size]; // 素数表
    int primeIdx;//当前使用的素数再素数表里面的下标

public:
    HashTable(int size=primes_[0], double loadFactor = 0.75)  
        : useBucketNum_(0)
        ,loadFactor_(loadFactor)
        ,primeIdx(0)
        {
            if(size != primes_[0])
            {
                for(;primeIdx<PRIME_size;primeIdx++)
                {
                    if(primeIdx > size || primes_[primeIdx]>size)
                    {
                        break;;
                    }
                }

                if(primeIdx == PRIME_size)
                {
                    primeIdx--;
                }
            }

            table_size = primes_[primeIdx];
            table_.resize(table_size);  
        }

    //不用写~HashTable（）函数，因为没有手动添加开辟内存

public:
    void insert(int key)
    {
        double fac = useBucketNum_*1.0 / table_size;
        cout << "factor: " << fac <<endl;

        if(fac > loadFactor_)
        {
            expand();
        }

        int idx = key % table_size;
        if(table_[idx].empty())  //空的直接加入
        {
            useBucketNum_ ++;
            table_[idx].emplace_front(key);
        }
        else  //先去重，在考虑释放插入
        {
            //使用全局的：：find范型算法，而不是条用自己的成员方法find；
            // auto it = ::find(table_[idx].begin(), table_[idx].end(),key);
            // if(it != table_[idx].end())
            // {
            //     table_[idx].emplace_front(key);
            // }
        }

    }

    void eras(int key)
    {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(),key);
        if(it != table_[idx].end())
        {
            table_[idx].emplace_front(key);
            {
                if(table_[idx].empty())
                {
                    useBucketNum_ --;
                }
            }
        }
    }

    bool find(int key)
    {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(),key);
        if(it != table_[idx].end())
        {
            return true;
        }
        return false;
    }


private:
    void expand()
    {
        ++primeIdx;
        if(primeIdx == PRIME_size)
        {
            throw "too much";
        }

        vector<list<int>> oldTable;
        table_.swap(oldTable);
        table_size = primes_[primeIdx];
        table_.resize(table_size);
        //!!!重新哈希
        useBucketNum_ = 0;
        for(auto list : oldTable)
        {
            for(auto key : list)
            {
                int idx = key % table_size;
                if(table_[idx].empty())  //空的直接加入
                {
                    useBucketNum_ ++;     
                }
                table_[idx].emplace_front(key);
            }
        }
    }
};



// int HashTable::primes_[PRIME_size] = {3,7,23,47,97,251,443,911,1471,42773};  //桶的size也就是，用来取余的取余数


//  int main()
//  {
//     HashTable htable;
//     htable.insert(45);
//     htable.insert(2);
//     htable.insert(55);
//     htable.insert(3);
//     htable.insert(74);

//     cout<< htable.find(24)<<endl;
//     htable.insert(24);
//     cout<< htable.find(24)<<endl;
//     htable.eras(74);
//     cout<< htable.find(74)<<endl;

//  }

