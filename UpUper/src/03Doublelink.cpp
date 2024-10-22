#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>

using namespace std;

struct Node
{
    Node(int data=0)
    : data_(data)
    , next_(nullptr)
    , pre_(nullptr){}
    int data_;
    Node* next_;
    Node* pre_;  
};


class DoubleLink
{
public:
    DoubleLink()
    {
        head_ = new Node();
    }
    ~DoubleLink()
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
    // 头插法
    void InserHead(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->pre_ = head_;
        if(head_->next_ != nullptr)
        {
            head_->next_->pre_ = node;
        }
        head_->next_ = node;
    }

    //尾插法
    void InserTail(int val)
    {
        Node*p = head_;
        while (p->next_ != nullptr)
        {
            p = p->next_;
        }

        Node* node = new Node(val);
        node->pre_ = p;
        p->next_ = node;
    }

    //节点删除
    void Remove(int val)
    {
        Node*p = head_->next_;
        while (p != nullptr)
        {
            if(p->data_ == val)
            {
                p->pre_->next_ = p->next_;
                if(p->next_ != nullptr)
                {
                    p->next_->pre_ = p->pre_;
                }
                delete p;
                return;
            }
            else
            {
                p = p->next_;
            }
        }
    }


    //输出
    void show()
    {
        Node*p = head_->next_;
        while (p != nullptr)
        {
            cout<<p->data_<<" ";
            p = p->next_;
        }
        cout<<endl;
    }

private:
    Node*head_;
};



class DoubleCircleLink
{
public:
    DoubleCircleLink()
    {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }
    ~DoubleCircleLink()
    {            
        Node *p = head_->next_;
        while (p != head_)
        {
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;
            p = head_->next_;
        }
        head_ = nullptr;
    }


public:
    // 头插法
    void InserHead(int val)
    {
        Node*p = head_->next_;
        Node* node = new Node(val);

        node->next_ = p;
        node->pre_ = head_;

        p->pre_ = node;
        head_->next_ = node;
    }

    //尾插法
    void InserTail(int val)
    {
        Node*p = head_->pre_;

        Node* node = new Node(val);
        node->pre_ = p;
        node->next_ = head_;

        p->next_ = node;
        head_->pre_ = node;

    }

    //节点删除
    void Remove(int val)
    {
        Node*p = head_->next_;
        while (p != head_)
        {
            if(p->data_ == val)
            {
                p->pre_->next_ = p->next_;
                p->next_->pre_ = p->pre_;
                delete p;
                return;
            }
            else
            {
                p = p->next_;
            }
        }
    }


    //输出
    void show()
    {
        Node*p = head_->next_;
        while (p != head_)
        {
            cout<<p->data_<<" ";
            p = p->next_;
        }
        cout<<endl;
    }

private:
    Node*head_;

};



// int main()
// {
//     DoubleCircleLink dlink;
//     dlink.InserHead(21);
//     dlink.InserHead(40);
//     dlink.InserHead(20);
//     dlink.InserHead(60);
//     dlink.InserHead(25);
//     dlink.InserHead(9);

//     dlink.show();
//     dlink.InserTail(9);
//     dlink.show();
//     dlink.Remove(60);
//     dlink.show();
// }