#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;


class LinkStack
{
public:
    LinkStack(): size_(0)
    {
        head_ = new Node;
    }

    ~LinkStack()
    {
        Node*p = head_;
        while (p != nullptr)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }


public://c++容器适配器stack，push、pop出栈、top、empty、size
    void push(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
        size_ ++;
    }

    void pop()
    {
        if(head_->next_ == nullptr)
        {
            throw"stack is empty";
        }
        Node*p = head_->next_;
        head_->next_ = p->next_;
        delete p;
        size_ --;
    }

    int top()
    {
        if(head_->next_ == nullptr)
        {
            throw"stack is empty";
        }
        return head_->next_->data_;
    }

    bool empty() const
    {
        return head_->next_ == nullptr;
    }

    int size() const
    {
        return size_;
    }

    private:

    private:
        struct Node
        {
            Node(int data = 0)
                :data_(data)
                ,next_(nullptr)
                {};
            int data_;
            Node* next_;
        };
        Node* head_;


        int* mpStack;
        int mtop;
        int mcap;
        int size_;
};


// int main()
// {
//     LinkStack s;
//     int arr[] = {11,22,45,78,96,50,4};

//     for(int val:arr)
//     {
//         s.push(val);
//     }

//     cout<<s.size()<<endl;
    
//     while (!s.empty())
//     {
//         cout<< s.top()<<" ";
//         s.pop();
//     }
    
// }
