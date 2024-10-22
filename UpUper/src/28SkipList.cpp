#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<time.h>
using namespace std;

/*
    和红黑树同样增删查时间复杂度-O（lon2（n））：跳跃表
    跳跃表： 每层都是一个有序链表，如果在leveli中出现，下面的链表也都会出现
            每个节点包含两个指针，一个指向下一层元素，一个指向同一层的下一个
             底层level包含所有元素

    插入时：采用抛硬币的方法（一直抛到正面为止）随机插入某一层(接近对数时间))，然后1-K层都插入该元素，1在最底层，若K大于现有的层数，则要添加层数
*/

class SkipList
{
private:
    struct Node
    {
        Node(int data = int())
            :data_(data)
            ,next_(nullptr)
            ,down_(nullptr)
        {}
        int data_;
        Node*next_;
        Node*down_;
    };

    struct HeadNode : public Node
    {
        HeadNode(int level)
            : level_(level)
        {}
        int level_;
    };
    
private:
    HeadNode*head_; //是Top层的head，第1层在最下面

public:
    SkipList()
    {
        head_ = new HeadNode(1);
    }
    ~SkipList()
    {
        int level = head_->level_;
        for(int i =0;i<level;i++)
        {
            Node *cur = head_->next_;
            while (cur != nullptr)
            {
                Node*temp = cur->next_;
                delete cur;
                cur = temp;
            }

            cur = head_;
            head_ = static_cast<HeadNode*> (head_->down_);
            delete cur; 
        }
    }

public:
    bool find(int data)
    {
        Node*pre = head_;
        Node*cur = pre->next_;

        for(;;)
        {
            if(cur != nullptr)
            {
                if(cur->data_ < data)
                {
                    pre = cur;
                    cur = cur->next_;
                    continue;
                }
                else if (cur->data_ == data)
                {
                    return true;
                }
            }

            if(pre->down_ == nullptr)
            {
                break;
            }

            pre = pre->down_;
            cur = pre->next_;
        }

        return false;
    }

    void add(int data)
    {
        if(find(data))
        {
            return;
        }

        int level = getLevel();
        if(level > head_->level_)
        {
            level = head_->level_ +1;
            HeadNode*hnode = new HeadNode(level);
            hnode->down_ = head_;
            head_ = hnode;   
        }

        Node** nodelist = new Node*[level];
        for(int i =level-1;i>=0;i--)
        {
            nodelist[i] = new Node(data);
            if(i<level-1)
            {
                nodelist[i]->down_ = nodelist[i+1];
            }
        }

        Node*head = head_;
        for(int i =head_->level_;i>level;i--)
        {
            head = head->down_;
        }

        Node *pre =head;
        Node*cur = pre->next_;

        for(int i =0;i<level;i++)
        {
            while (cur!= nullptr && cur->data_ < data)
            {
                pre = cur;
                cur = cur->next_;
            }

            nodelist[i]->next_ = cur;
            pre->next_ = nodelist[i];

            pre = pre->down_;
            if(pre!=nullptr)
            {
                cur = pre->next_;
            }

            
        }     
        delete[] nodelist;
        nodelist = nullptr;
    }

    void show() const
    {
        Node*head =head_;
        while (head!= nullptr)
        {
            Node*cur = head->next_;
            while (cur != nullptr)
            {
                cout <<cur->data_ << " ";
                cur = cur->next_;
            }
            cout << endl;
            head = head->down_;
        }
        cout<<endl;
    }

    void remove(int data)
    {
        Node*pre = head_;
        Node*cur = pre->next_;

        while (1)
        {
            if(cur != nullptr)
            {
                if(cur->data_ < data)
                {
                    pre = cur;
                    cur = cur->next_;
                    continue;
                }
                else if (cur->data_ == data)
                {
                    pre->next_ = cur->next_;
                    delete cur;        
                }
            }

            if(pre->down_ == nullptr)
            {
                break;
            }

            pre = pre->down_;
            cur = pre->next_;
        }
    }

private:
    int getLevel()const
    {
        int level = 1;
        while (rand()%2 == 1)
        {
            level++;
        }
        return level;
    }

};

/*
int main()
{
    SkipList list;
    srand(time(nullptr));

    for(int i = 0;i<20;i++)
    {
        list.add(rand()%100);
    }

    list.add(15);
    list.show();

    list.remove(15);
    list.show();


}*/