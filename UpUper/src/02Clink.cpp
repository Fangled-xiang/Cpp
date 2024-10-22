#include<DataStruct.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>

using namespace std;

struct Node
{
    Node(int data=0):data_(data), next_(nullptr){}
    int data_;
    Node* next_;
};

class Clink
{
    public:
        Clink()
        {
            head_ = new Node();//初始化指向头结点
        }
        ~Clink()//不能直接删，删掉头结点就找不到后面的了
        {
            Node *p = head_;
            while (p != nullptr)
            {
            head_ = head_->next_;
            delete p;
            p = head_;
            }
            head_ = nullptr;
        }


    public:
        //尾插法:
        void InserTail(int val)
        {
            //先找到末尾节点
            Node*p = head_;
            while(p->next_ != nullptr)
            {
                p = p->next_;
            }

            //生成新节点
            Node*  node = new Node(val);
            p->next_ = node;
        }

        //头插法
        void InserHead(int val)
        {
            Node* node = new Node(val);
            node->next_ = head_->next_;
            head_->next_ = node;
        }

        //节点删除
        void remove(int val)
        {
            Node*q = head_;
            Node*p = head_->next_;

            while (p != nullptr)
            {
                if(p->data_ == val)
                {
                    q->next_ = p->next_;
                    delete p;
                    return;
                }
                else
                {
                    q = p;
                    p = p->next_;
                }
            }
        }

        void removeAll(int val)
        {
            Node*q = head_;
            Node*p = head_->next_;

            while (p != nullptr)
            {
                if(p->data_ == val)
                {
                    q->next_ = p->next_;
                    delete p;
                    p = q->next_;
                }
                else
                {
                    q = p;
                    p = p->next_;
                }
            }
        }



        //打印
        void show()
        {
            Node*p = head_->next_;
            while (p != nullptr)
            {
                cout << p->data_ <<" ";
                p = p->next_;
            }
            cout<<endl;
            
        }



    private:
        Node*head_;

        friend void reverseLink(Clink &link);
        friend void hebin(Clink &link1, Clink &link2);
        friend void hebintest(Clink &link);
        bool IsCricle(Node *head, int &val);
};


void Clink_test()
{
    // Clink link1, link2;
    // srand(time(0));
    // for(int i = 0;i<10;i++)
    // {
    //     int val = rand()%100;
    //     link1.InserHead(val);
    //     // link2.InserTail(val);
    //     // cout << val <<" ";
    // }
    // cout<<endl;
    // link1.show();

    // reverseLink(link1);
    // link1.show();

    // // link2.show();

    // // link1.InserTail(200);
    // // link1.show();
    // // link1.remove(200);
    // // link2.show();

    // Clink link;
    // hebintest(link);

} 


void reverseLink(Clink &link) //逆序
{
    Node*head = link.head_;
    Node*p = head->next_;
    if(p == nullptr)
    {
        return;
    }
    head->next_ = nullptr;

    while (p != nullptr)
    {
        Node*q = p->next_;

        p->next_ = head->next_;
        head->next_ =p;
        
        p = q;
    }
}

//有序链表合并，新的有序链表
void hebin(Clink &link1, Clink &link2)
{
    Node*p = link1.head_->next_;
    Node*q = link2.head_->next_;
    Node*last = link1.head_;

    while (p != nullptr || q != nullptr)
    {
        if(p == nullptr)
        {
            last->next_ = q;
            q = q->next_;
            continue;
        }

        if(q == nullptr)
        {
            last->next_ = p;
            p = p->next_;
            continue;
        }
        
        if(p->data_ > q->data_)
        {
            last->next_ = q;
            q = q->next_;
        }
        else
        {
            last->next_ = p;
            p = p->next_;
        } 

        last = last->next_;   
    }
}


void hebintest(Clink &link)
{
    Clink link1,link2;
    int a[6] = {2,6,7,11,20,55};
    int b[5] = {1,5,9,11,33};
    for(int i=0;i<6;i++)
    {
        link1.InserTail(a[i]);
    }
    for(int i=0;i<5;i++)
    {
        link2.InserTail(b[i]);
    }
    link1.show();
    link2.show();

    // hebin(link1, link2);
    // link1.show();
    hebin(link2, link1);
    link2.show();

}


//找环的入口-双指针-快慢指针的应用（判断有环）
bool IsCricle(Node *head, int &val)
{
    Node*fast = head;
    Node*slow = head;
    while (fast != nullptr && fast->next_ != nullptr)
    {
        slow = slow->next_;
        fast = fast->next_->next_;

        if (fast == slow)
        {
            fast = head;
            {
                while (fast != slow)
                {
                    slow = slow->next_;
                    fast = fast->next_;
                }
            }
            val = slow->data_;
            return true;
        }
    }
    return false;
    
}

//判断两个链表是否相交
bool IsMerge(Node *head1, Node*head2, int &val)
{
    Node*p = head1->next_;
    Node*q = head2->next_;

    int len1=0 ,len2 =0;

    while (p != nullptr)
    {
        len1++;
        p = p->next_;
    }

    while (q != nullptr)
    {
        len2++;
        q = q->next_;
    }

    p = head1->next_;
    q = head2->next_;

    if(len1>len2)
    {
        for(int i=0;i<(len1-len2);i++)
        {
            p = p->next_;
        }
    }
    if(len1<len2)
    {
        for(int i=0;i<(len2-len1);i++)
        {
            q = q->next_;
        }
    }

    while (q != p && q != nullptr && q != nullptr)
    {
        p = p->next_;
        q = q->next_;
        if(q == p)
        {
            val = q->data_;
            return true;
        }
    }

    return false; 
}



// int main()
// {
    // Node head1,head2, n1(25),n2(67),n3(32),n4(18),n5(22);
    // head1.next_ = &n1;
    // n1.next_ = &n2;
    // n2.next_ = &n3;
    // n3.next_ = &n4;

    // head2.next_ = &n5;
    // n5.next_ = &n3;

    // // int val;
    // // if(IsCricle(&head,val))
    // // {
    // //     cout<<"in : "<<val<<endl;
    // // }

    // int val;
    // if(IsMerge(&head1,&head2,val))
    // {
    //     cout<<"Merge in : "<<val<<endl;
    // }

// }