#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

class LinkQueue
{
private:
    struct Node
    {
        Node(int data=0)
            : data_(data)
            , next_(nullptr)
            , pre_(nullptr)
        {}
        int data_;
        Node* next_;
        Node* pre_;  
    };

    Node*head_;


public:
    LinkQueue()
    {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }

    ~LinkQueue()
    {
        Node*p =head_->next_;
        while (p != head_)
        {
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;
            p = head_->next_;
        }
        delete head_;
        head_ = nullptr;
    }

public:
    //入队
    void push(int val)
    {
        Node*p = head_->pre_;
        Node*node = new Node(val);
        node->pre_ = p;
        node->next_ = head_;
        p->next_ = node;
        head_->pre_ = node;
    }

    void pop()
    {
        Node*p =head_->next_;
        head_->next_ = p->next_;
        p->next_->pre_ = head_;
        delete p;
    }

    int front() const
    {
        if(head_->next_ == head_)
        {
            throw"empty";
        }
        return head_->next_->data_;
    }

    int back() const
    {
        if(head_->next_ == head_)
        {
            throw"empty";
        }
        return head_->pre_->data_;
    }

};




// int main()
// {
//     LinkQueue s;
//     int arr[] = {11,22,45,78,96,50,4,100,200,300,400,500,666};

//     for(int val:arr)
//     {
//         s.push(val);
//     }

//     cout<< s.front()<<endl;
//     cout<< s.back()<<endl;
// }
