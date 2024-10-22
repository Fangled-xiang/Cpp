//堆排序：完全二叉树（最后一层叶子节点都是靠左排列的），二叉堆：大根堆，小根堆（当前节点值大于孩子节点则是大根堆，小于是小根堆）
//完全二叉树：当前节点i：左孩子是2*i+1，右孩子是2*i+2（画画就知道了），然后再数组上存储即可 
// i = （n-1）/2  ，就是上面的式子反求父节点 即为最后一个有孩子的节点下标（从0开始），堆顶值最大/小，只能操作堆顶

//入堆（末尾）操作：进行上浮操作，和父节点比较大小进行交换（覆盖即可，没必要交换，找入队位置），保证满足大小根堆条件，直到0结束

//出堆（堆顶）：在将末尾元素放在堆顶，然后进行下沉，和入堆反过来

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<functional>
using namespace std;

class PriorityQueue//也叫优先级队列
{
public:
    using Comp = function<bool(int,int)>;
    PriorityQueue(Comp comp = greater<int>())  //调用时只需要传入一个比较器函数即可
        :size_(0)
        ,cap_(20)
        ,comp_(comp)
        {
            que_ = new int[cap_];
        }

    ~PriorityQueue()
    {
        delete[]que_;
        que_ = nullptr;
    }

public:
    //入堆操作
    void push(int val)
    {
        if(size_ == cap_)
        {
            int*p = new int[cap_*2];
            memcpy(p,que_,cap_* sizeof(int));
            delete[]que_;
            que_ = p;
            cap_*=2;
        }
        else
        {
            siftup(size_ ,val);//上浮
        }
        size_ ++;
    }

    void pop()
    {
        size_ --;
        if(size_ == 0)
        {
            return;
        }
        else
        {
            shiftdown(0,que_[size_]); //从0号位开始下沉
        }
    }

    int top()const
    {
        if(size_ == 0)
        {
            throw"empty";
        }
        return que_[0];
    }

    bool empty()const
    {
        return size_ == 0;
    }
    
private:
    void siftup(int i,int val) // 大根堆
    {
        while (i> 0)
        {
            int father = (i-1)/2;
            if(comp_(val , que_[father]))
            {
                que_[i] = que_[father];
                i = father;
            }
            else
            {
                break;
            }
        }

        que_[i] = val;
    }

    void shiftdown(int i,int val)
    {
        while(i <= (size_ -1 -1)/2) //有孩子
        {
            int child = 2*i+1;
            if(child +1 < size_  && comp_(que_[child+1],que_[child]))//有右孩子且右边大,因为大的才往上提
            {
                child = child +1;
            }
            if(comp_(que_[child],val))
            {
                que_[i] = que_[child];
                i = child;
            }
            else
            {
                break;
            }
        }

        que_[i]=val;
    }

private:
    int *que_;
    int size_;
    int cap_;
    Comp comp_; //比较器对象


};






//堆排序：从第一个非叶子节点（n-1）/2：（n是下标）开始一直到堆顶，进行下沉操作，把二叉堆调整成一个大根堆
void shiftDown(int arr[],int i,int size)  //i是开始位置
{
    int val = arr[i];
    //while( i < (size-1-1)/2)//这个条件不可以,因为当size为2时也不进入，<=时，size为1的时候又会进入，把val值覆盖上去
    while (i < size/2) 
    {
        int child = 2*i+1;
         if(child +1 < size  && arr[child+1] >arr[child] )//有右孩子且右边大,因为大的才往上提
        {
            child = child +1;
        }
        if(arr[child] > val)
        {
            arr[i] = arr[child];
            i = child;
        }
        else
        {
            break;
        }
        arr[i] = val;
    }
}
 void Heapsort(int arr[],int size)
 {
    int n = size -1;//下标
    for(int i =(n-1)/2;i>=0;i--)
    {
        shiftDown(arr,i,size);//调整成大根堆
    }

    //堆顶和末尾调换,然后从堆顶进行下沉操作调整成大根堆(相当于在shiftdowm里面只进行了一次就行，因为最大的肯定是下面中的一个)
    for(int i =n ;i>0;i--)  //i要有1，虽然不会进行shiftdown，但还要调换前一步的
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        shiftDown(arr,0,i); //每次调整一次考虑的个数减一，将剩下的调整成大根堆，再取堆顶
    }


 }




// int main()
// {
//     // // PriorityQueue que;//默认是大根堆，完成大到小排序

//     // PriorityQueue que( [](int a,int b){return a < b;}); //小根堆实现,换个比较器函数即可(新奇的写法)

//     // srand(time(NULL));

//     // for (int i = 0; i < 40; i++)
//     // {
//     //     que.push( rand()%100 );
//     // }

//     // while (!que.empty())
//     // {
//     //     cout<<que.top()<<" "; //堆顶值是最大的，完成排序
//     //     que.pop(); //出堆
//     // }
//     // cout << endl;



//     int arr[10];
//     for (int i = 0; i < 10; i++)
//     {
//         arr[i] = rand()%100 +1;
//     }
//     for(int val : arr)
//     {
//         cout<< val <<" ";
//     }
//     cout << endl;


//     Heapsort(arr, 10);
//     for(int val : arr)
//     {
//         cout<< val <<" ";
//     }
//     cout << endl;


    
// }