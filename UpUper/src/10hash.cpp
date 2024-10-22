//hash表：用于对查询需要非常快的场景，-散列表，通过一个映射关系得到他的存储位置（放的是存储位置），然后去存放位置取值
//（一般是取余，但是也会有多个数放一个桶，出现哈希冲突（可以用线性探测法进行解决）从而使得一个桶放一个，一般是和素数取余，
//比如11，就能取余得到11个桶，桶的size就是11，分为一个个的桶了就，
//当一个桶装满3/4时，往往就需要扩容了，而且对所有的值都需要重新哈希）
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;


//线性探测！！！哈希表实现
enum State
{
    STATE_UNUSE, //未使用的桶
    STATE_USING, //正在使用的桶
    STATE_DEL, //元素被删了的桶
};

//一个桶
struct Bucket
{
    Bucket(int key = 0, State state = STATE_UNUSE)
        : key_(key)
        , state_(state)
        {}
    int key_;     //数据存储位置
    State state_;
};
 
//哈希表类型
class HashTable
{
public:
    HashTable(int size=primes_[0], double loadFactor = 0.75)  //用户需要传入的
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
            table_ = new Bucket[table_size];  //桶类型的数组
        }

    ~HashTable()
    {
        delete[]table_;
        table_ = nullptr;
    }

public:
    //插入函数
    bool insert(int key)
    {
        //考虑扩容
        double fac = useBucketNum_*1.0 / table_size;

        //cout<<"useBucketNum_: "<<useBucketNum_<<endl;
        // cout<<"table_size: "<<table_size<<endl;
        cout << "factor: " << fac <<endl;

        if(fac > loadFactor_)
        {
            cout<<"expand!!!"<<endl;
            expand();
        }

        int idx = key % table_size;
        int i =idx;
        do
        { 
            if(table_[i].state_ != STATE_USING)
            {
                table_[i].state_ = STATE_USING;
                table_[i].key_ = key;
                useBucketNum_++;
                return true;
            }
            i = (i+1)%table_size;
        }while(i != idx);

        return false;
    }

    //删除（多个重复的一起删除）
    bool eras(int key)
    {
        int idx = key % table_size;

        int i =idx;
        do
        {
            if(table_[i].state_ == STATE_USING && table_[i].key_ == key)
            {
                table_[i].state_ = STATE_DEL;
            }
            i = (i+1)%table_size;
        } while (i != idx && table_[i].state_ != STATE_UNUSE);

        if(i == idx || table_[i].state_ != STATE_UNUSE)
            return false;
        else
            return true;
    }

    //查询
    bool find(int key)
    {
        int idx = key % table_size;

        int i =idx;
        do
        {
            if(table_[i].state_ == STATE_USING && table_[i].key_ == key)
            {
                return true;
            }
            i = (i+1)%table_size;
        } while (i != idx && table_[i].state_ != STATE_UNUSE);

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

        Bucket *newTable = new Bucket[primes_[primeIdx]];
        for(int i = 0;i<table_size;i++)
        {
            if(table_->state_ == STATE_USING)
            {
                int idx = table_[i].key_ % primes_[primeIdx];
                int k = idx;
                do
                {
                    if(newTable[k].state_ != STATE_USING)
                    {
                        newTable[k].state_ = STATE_USING;
                        newTable[k].key_ = table_[i].key_;
                        break;
                    }
                } while (k != idx);
                
            }

            delete[]table_;
            table_ = newTable;
            table_size = primes_[primeIdx];
        }
    }

private:
    Bucket* table_;  //指针指向动态开辟的哈希表
    int table_size;  //哈希表长度；
    int useBucketNum_; //使用桶的个数
    double loadFactor_; //哈希表装载因子，经验可取3/4

    static const int PRIME_size = 10;//素数表大小
    static int primes_[PRIME_size]; // 素数表

    int primeIdx;//当前使用的素数再素数表里面的下标

 };


//要记得注释，否则下个文件不能用
// int HashTable::primes_[PRIME_size] = {3,7,23,47,97,251,443,911,1471,42773};  //桶的size也就是，用来取余的取余数

//  int main()
//  {
//     HashTable htable(5,0.3);
//     htable.insert(45);
//     htable.insert(2);
//     htable.insert(55);
//     htable.insert(3);
//     htable.insert(74);

//     // cout<< htable.find(24)<<endl;
//     // htable.insert(24);
//     // cout<< htable.find(24)<<endl;
//     // htable.eras(74);
//     // cout<< htable.find(74)<<endl;

//  }